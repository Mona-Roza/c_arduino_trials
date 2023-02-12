### Devre Şeması:

[![](https://github.com/Mona-Roza/c_arduino_trials/blob/main/arduino_trial_11/circuit_diagram.png)](https://github.com/Mona-Roza/c_arduino_trials/blob/main/arduino_trial_11/circuit_diagram.png)

### [Tinkercad](https://www.tinkercad.com/things/h3dHzyGhtCk) üzerinden simüle edebilirsiniz.

# MCU C Kodu Derleme ve Yükleme
İsteğe göre aşağıda "Derleme" ve "Yükleme" şeklinde başlıklandırılmış komutlar kullanılarak veya her dosyanın içerisinde bulunan "compile_and_push.sh" scripti kullanılarak derleme ve yükleme yapılabilir.

:warning: compile_and_push.sh scriptinin kullanılabilmesi için öncelikle bu scriptin çalıştırılmasına izin verilmelidir. İzin vermek için 

```bash
chmod 755 compile_and_push.sh
```

komutu bir kereye mahsus çalıştırılmalıdır. Ardından
```bash
./compile_and_push.sh
```
komutu ile derleme ve yükleme yapabilirsiniz.

## Derleme : 

1. Aşağıdaki derleme komutunu MCU'nuzun frekans ve modeline göre düzenleyin. Eğer derlenecek dosyanızın adı main.c değilse, son kısmı düzenlemeyi unutmayın.
```
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o main.o main.c
```

2. Obje dosyasını oluşturmak için önceden derlediğiniz dosya üzerinden aşağıdaki komutu çalıştırın. 
```
avr-gcc -mmcu=atmega328p main.o -o main
```

3. Hex dosyasını oluşturmak için aşağıdaki komutu çalıştırın.
```
avr-objcopy -O ihex -R .eeprom main main.hex
```

## Yükleme

Aşağıdaki yükleme komutunu çalıştırabilmek için, öncelikle mcu modelinizi değiştirmeniz, kartınızı bağladığınız usb portunu değiştirmeniz ve son olarak eğer hex dosyanızın ismi farklı ise bunu değiştirmniz gerekmektedir
```
avrdude -F -V -c arduino -p ATMEGA328P -P  /dev/cu.usbserial-110 -b 115200 -U flash:w:main.hex
```