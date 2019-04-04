print-%:
	@echo '$*=$($*)'

CONTIKI_PROJECT = sdn-wise
all: $(CONTIKI_PROJECT)

CONTIKI = ../contiki
CONTIKI_WITH_RIME = 1

COOJA ?= 1
ifneq ($(COOJA),)
    CFLAGS += -DCOOJA=$(COOJA)
endif

SINK ?= 0
ifneq ($(SINK),)
    CFLAGS += -DSINK=$(SINK)
endif

SDN_WISE_DEBUG ?= 0
ifneq ($(SDN_WISE_DEBUG),)
    CFLAGS += -DSDN_WISE_DEBUG=$(SDN_WISE_DEBUG)
endif

# SDN Configuration
BEACON_FREQ ?= 10
ifneq ($(BEACON_FREQ),)
    CFLAGS += -DSDN_CONF_BEACON_PERIOD=$(BEACON_FREQ)
endif
REPORT_FREQ ?= 60
ifneq ($(REPORT_FREQ),)
    CFLAGS += -DSDN_CONF_CONTROLLER_UPDATE_PERIOD=$(REPORT_FREQ)
endif
INITIALISATION_PERIOD ?= 10
ifneq ($(INITIALISATION_PERIOD),)
    CFLAGS += -DINITIALISATION_PERIOD=$(INITIALISATION_PERIOD)
endif
RULE_TTL ?= 1
ifneq ($(RULE_TTL),)
    CFLAGS += -DSDN_CONF_FT_LIFETIME=$(RULE_TTL)
endif

# Data Configuration
DATA_RATE ?= 60
ifneq ($(DATA_RATE),)
    CFLAGS += -DDATA_RATE=$(DATA_RATE)
endif
ifneq ($(TX_NODES),)
    CFLAGS += -DTX_NODES=$(TX_NODES)
endif

# Power Logging
WITH_PWR_STATS ?= 1
ifeq ($(WITH_PWR_STATS),1)
    CFLAGS += -DWITH_PWR_STATS=1 -DSDN_STATS_PERIOD=60
    CFLAGS += -DCONTIKIMAC_CONF_COMPOWER=1 -DWITH_COMPOWER=1
endif

# Logging levels
LOG_LEVEL_SDN ?= LOG_LEVEL_STAT
ifneq ($(LOG_LEVEL_SDN),)
    CFLAGS += -DLOG_CONF_LEVEL_SDN=$(LOG_LEVEL_SDN)
endif

PROJECT_SOURCEFILES += sdn-wise-pwr.c log-ng.c flowtable.c packet-buffer.c address.c neighbor-table.c packet-handler.c node-conf.c packet-creator.c
TARGETDIRS += ../targets
CFLAGS += -DPROJECT_CONF_H=\"project-conf.h\"

include $(CONTIKI)/Makefile.include
