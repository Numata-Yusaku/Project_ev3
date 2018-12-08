### Makefileパス
mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

### ソースオブジェクトファイル
APPL_COBJS +=	\
			main.o \
			common.o \
			rsi_common.o \
			fs.o \
			hw.o \
			lcd.o \
			motor.o \
			sensor.o \
			extend.o \
			task.o \
			taskin.o \
			bt.o \
			btin.o \
			btin_recv.o \
			btin_send.o \
			btin_message.o \
			btin_log.o \
			lt.o \
			ltin.o \
			ltin_recv.o \
			ltin_send.o \
			ltin_balance.o \
			ltin_log.o \

### ソースパス
APPL_DIR +=		\
			$(mkfile_path)robo_main \
			$(mkfile_path)robo_main/RSI \
			$(mkfile_path)robo_main/RSI/Filesystem \
			$(mkfile_path)robo_main/RSI/Hardware \
			$(mkfile_path)robo_main/RSI/Lcd \
			$(mkfile_path)robo_main/RSI/Motor \
			$(mkfile_path)robo_main/RSI/Sensor \
			$(mkfile_path)robo_main/RSI/Extend \
			$(mkfile_path)robo_main/GEN/COMMON \
			$(mkfile_path)robo_main/GEN/TASK \
			$(mkfile_path)robo_main/GEN/BT \
			$(mkfile_path)robo_main/APL/LT \

### ヘッダパス
INCLUDES +=		\
			-I$(mkfile_path)robo_main \
			-I$(mkfile_path)robo_main/RSI \
			-I$(mkfile_path)robo_main/RSI/Filesystem \
			-I$(mkfile_path)robo_main/RSI/Hardware \
			-I$(mkfile_path)robo_main/RSI/Lcd \
			-I$(mkfile_path)robo_main/RSI/Motor \
			-I$(mkfile_path)robo_main/RSI/Sensor \
			-I$(mkfile_path)robo_main/RSI/Extend \
			-I$(mkfile_path)robo_main/GEN/COMMON \
			-I$(mkfile_path)robo_main/GEN/TASK \
			-I$(mkfile_path)robo_main/GEN/BT \
			-I$(mkfile_path)robo_main/APL/LT \
