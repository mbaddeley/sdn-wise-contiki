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

# SDN_WISE_DEBUG ?= 1
ifneq ($(SDN_WISE_DEBUG),)
    CFLAGS += -DSDN_WISE_DEBUG=$(SDN_WISE_DEBUG)
endif

# SDN Configuration
REPORT_FREQ ?= 60
ifneq ($(REPORT_FREQ),)
    CFLAGS += -DSDN_CONF_CONTROLLER_UPDATE_PERIOD=$(REPORT_FREQ)
endif
RULE_TTL ?= 20
ifneq ($(RULE_TTL),)
    CFLAGS += -DSDN_CONF_FT_LIFETIME=$(RULE_TTL)
endif
DATA_RATE ?= 75
ifneq ($(DATA_RATE),)
    CFLAGS += -DDATA_RATE=$(DATA_RATE)
endif

# Logging levels
LOG_LEVEL_SDN ?= LOG_LEVEL_STAT
ifneq ($(LOG_LEVEL_SDN),)
    CFLAGS += -DLOG_CONF_LEVEL_SDN=$(LOG_LEVEL_SDN)
endif

PROJECT_SOURCEFILES = log-ng.c flowtable.c packet-buffer.c address.c neighbor-table.c packet-handler.c node-conf.c packet-creator.c
TARGETDIRS += ../targets
CFLAGS += -DPROJECT_CONF_H=\"project-conf.h\"

include $(CONTIKI)/Makefile.include
