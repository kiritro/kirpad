# MCU name
MCU = atmega32u4

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = atmel-dfu

EXTRAFLAGS += -flto             #优化编译

# Yes 
COMBO_ENABLE = yes				# Key Combos
EXTRAKEY_ENABLE = yes        
ENCODER_ENABLE = yes       
NKRO_ENABLE = yes 
OLED_DRIVER_ENABLE = yes          
RGBLIGHT_ENABLE = yes  
VIA_ENABLE = yes    
LTO_ENABLE = yes                 #优化编译      

# No
MOUSEKEY_ENABLE = no           # Mouse keys
COMMAND_ENABLE = no            # Commands for debug and configuration
BOOTMAGIC_ENABLE = no 
SLEEP_LED_ENABLE = no 
MIDI_ENABLE = no            
UNICODE_ENABLE = no         
BLUETOOTH_ENABLE = no      
AUDIO_ENABLE = no 
BACKLIGHT_ENABLE = no  
CONSOLE_ENABLE = no 
KEY_LOCK_ENABLE = no  
