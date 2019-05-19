











typedef int SPI_HandleTypeDef;

SPI_HandleTypeDef hspi2;



typedef enum

{

  GPIO_PIN_RESET = 0,

  GPIO_PIN_SET

}GPIO_PinState;



struct gpio_struct{

  int gpioa[11];

  int gpiob[11];

  int gpioc[11];

  int gpiod[11];

  int gpioe[11];

}test_gpio_data;

void HAL_Delay(uint32_t delay);





void HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t * data, uint16_t len, uint32_t timeout);



void HAL_GPIO_WritePin(int *gpio_port, int gpio_pin, GPIO_PinState state);
