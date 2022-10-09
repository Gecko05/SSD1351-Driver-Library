package main

import (
	"fmt"
	"image"
	"image/color"
	"log"
	"net"
	"os"
	"time"

	"gioui.org/app"
	"gioui.org/f32"

	"gioui.org/io/system"
	"gioui.org/layout"
	"gioui.org/op"
	"gioui.org/op/paint"
)

const (
	SERVER_HOST = "localhost"
	SERVER_PORT = "9988"
	SERVER_TYPE = "tcp"
)

var screenBuffer []byte

func processClient(connection net.Conn) {
	buffer := make([]byte, 32768)
	mLen, err := connection.Read(buffer)
	if err != nil {
		fmt.Println("Error reading:", err.Error())
	}
	// Look for whole frames
	if mLen == 32768 {
		screenBuffer = buffer[:32768]
	}
	connection.Close()
}

func initServer() {
	fmt.Println("Server Running...")
	server, err := net.Listen(SERVER_TYPE, SERVER_HOST+":"+SERVER_PORT)
	if err != nil {
		fmt.Println("Error listening:", err.Error())
		os.Exit(1)
	}
	defer server.Close()
	fmt.Println("Listening on " + SERVER_HOST + ":" + SERVER_PORT)
	fmt.Println("Waiting for client...")
	for {
		connection, err := server.Accept()
		if err != nil {
			fmt.Println("Error accepting: ", err.Error())
			os.Exit(1)
		}
		processClient(connection)
	}
}

func main() {
	go initServer()
	go func() {
		w := app.NewWindow(app.Size(256, 256), app.MinSize(256, 256), app.MaxSize(256, 256))
		go func() {
			timer1 := time.NewTicker(time.Second / 30)
			for {
				<-timer1.C
				w.Invalidate()
			}
		}()
		err := run(w)
		if err != nil {
			log.Fatal(err)
		}
		os.Exit(0)
	}()
	app.Main()
}

func drawImage(ops *op.Ops, img image.Image, w *app.Window) {
	imageOp := paint.NewImageOp(img)
	imageOp.Add(ops)
	t := op.Affine(f32.Affine2D{}.Scale(f32.Pt(0, 0), f32.Pt(2, 2)))
	t.Push(ops)
	paint.PaintOp{}.Add(ops)
}

func run(w *app.Window) error {
	var ops op.Ops
	for {
		e := <-w.Events()
		switch e := e.(type) {
		case system.DestroyEvent:
			return e.Err
		case system.FrameEvent:
			gtx := layout.NewContext(&ops, e)

			minPoint := image.Point{0, 0}
			maxPoint := image.Point{128, 128}
			rect := image.Rectangle{minPoint, maxPoint}
			myImage := image.NewNRGBA(rect)
			for i := 0; i < 32768; i += 2 {
				if len(screenBuffer) == 32768 {
					// 1 1 1 1 2 2 2 2 3 3 3 3 4 4 4 4
					// b b b b b g g g g g g r r r r r
					r := screenBuffer[i+1] & 0x1F << 3
					b := screenBuffer[i] & 0xF8
					g := (((screenBuffer[i] & 0x07) << 4) | ((screenBuffer[i+1] & 0xE0) >> 5)) << 1
					newColor := color.NRGBA{r, g, b, 255}
					// The image is flipped horizontally
					newI := 32767 - i
					myImage.SetNRGBA((newI/2)%128, int((i/2)/128), newColor)
				} else {
					newColor := color.NRGBA{0, 200, 0, 255}
					myImage.SetNRGBA((i/2)%128, int((i/2)/128), newColor)
				}
			}
			drawImage(gtx.Ops, myImage, w)

			e.Frame(gtx.Ops)
		}
	}
}
