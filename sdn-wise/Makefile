CONTIKI_PROJECT = sdn-wise
all: $(CONTIKI_PROJECT)

CONTIKI = ../contiki
CONTIKI_WITH_RIME = 1

# SDN_WISE_DEBUG ?= 1
ifneq ($(SDN_WISE_DEBUG),)
    CFLAGS += -DSDN_WISE_DEBUG=$(SDN_WISE_DEBUG)
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
