
# Começando com o MicroPython no ESP8266

A)	Material necessário

•	Cabo USB

•	Alguma ESP8266 board: como NodeMCU ou Adafruit Huzzah

•	512Kb de FLASH do ESP8266

•	Download do firmware  ( http://micropython.org/download#esp8266 )

 Passo a passo:

1)	Com o firmware .bin do MicroPython baixado, necessitamos agora instala-lo na ESP8266 board. O primeiro passo é colocar o dispositivo no boot-loader mode e em seguida copiar o firmware. 

Esta etapa é especifica dependendo de qual placa você possui, para ESP8266 veja como https://www.youtube.com/watch?v=L3Al36eRrl4

2)	O segundo passo é passar o firmware para a placa, para fazer isso será necessário utilizar o ESPTOOL, devido a compatibilidades, para gravar o firmware. 

 Usando o esptool, 
>> esptool.py --port /dev/ttyUSB0 erase_flash

>> esptool.py --port /dev/ttyUSB0 --baud 460800 write_flash --flash_size=detect 0 esp8266-20170108-v1.8.7.bin

 Se algum erro acontecer voce pode trocar a porta, por exemplo trocar o baundrate para 115200. Também note que o nome do arquivo do firmware deve ser exatamente o mesmo indicado. Para algumas placas você necessitará fazer o "deploy firmware", usando -fm dio option. 

3)	Com o firmware do MicroPython instalado corretamente, agora podemos acessa-lo via serial. Utilize o baundrate de 115200, na porta conectada pela placa.  Para acessar via Linux por exemplo: 
>> picocom /dev/ttyUSB0 -b115200
 
Para testar que o MicroPython está rodando ok, tente escrever um hello world:  print(‘hello world’).
Running Code From A Script

Você deve ter notado que todo código ou comando Python rodado até o momento no firmware do MicroPython no NodeMCU foi inserido através do serial console!! Para poder rodar um script python, um código de uma implementação como piscar um LED você deve salvar o arquivo Python e rodar no boot do firmware. Note que no ESP8266 não temos a opção de rodar o arquivo direto de um cartão SD, por exemplo. 

 Para rodar scripts no boot você necessitará de uma modificacão no firmware do MicroPython. Rode o editor de texto no "S.O." do MicroPython! Você pode usar o nano, veja a seguir:

1.	cd ~/micropython/esp8266/scripts/
2.	nano main.py

Criando esse arquivo poderemos criar um código para piscar o LED da placa NodeMCU!

	# This script is run on boot
	import pyb
	pin = pyb.Pin(14, pyb.Pin.OUT_PP)
	    while True:
	         pin.value(1)
	         pyb.delay(1000)
	         pin.value(0)
	         pyb.delay(1000)


REFERÊNCIAS

•	http://docs.micropython.org/en/latest/esp8266/esp8266/tutorial/intro.html#deploying-the-firmware 

•	https://learn.adafruit.com/building-and-running-micropython-on-the-esp8266/overview
