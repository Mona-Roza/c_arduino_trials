# MCU C Kodu Derleme ve Yükleme

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

# Yükleme
avrdude -F -V -c arduino -p ATMEGA328P -P  /dev/cu.usbserial-110 -b 115200 -U flash:w:main.hex

# Kütüphanelerin Tanınması

.vscode içerisinde bulunan c_cpp_properties.json dosyasının içerisine aşağıdakilerin eklenmesi ile kütüphaneler tanınır hale gelecektir. 

> :warning:
> Bu içerik configurations listesine bir öge olarak eklenmelidir.

````
  
        {
            "name": "AVR",
            "intelliSenseMode": "${default}",
            "compilerPath": "/opt/homebrew/bin/avr-gcc",
            "cStandard": "${default}",
            "cppStandard": "${default}",
            "includePath": [],
            "compilerArgs": [
                "-g",
                "-Os",
                "-Wall",
                "-Wextra",
                "-fpermissive",
                "-fno-exceptions",
                "-fno-threadsafe-statics",
                "-pipe",
                "-mmcu=ATmega328p",
                "-DF_CPU=8000000UL"
            ],
            "macFrameworkPath": [
                "/System/Library/Frameworks",
                "/Library/Frameworks"
            ]
        }
   
````


