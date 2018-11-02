#ifndef __ASUS_FG_H
#define __ASUS_FG_H

#include "linux/asusdebug.h"

#define BATTERY_TAG "[BAT][BMS]"
#define ERROR_TAG "[ERR]"
#define BAT_DBG(...)  printk(KERN_INFO BATTERY_TAG __VA_ARGS__)
#define BAT_DBG_L(level, ...)  printk(level BATTERY_TAG __VA_ARGS__)
#define BAT_DBG_E(...)  printk(KERN_ERR BATTERY_TAG ERROR_TAG __VA_ARGS__)

#define FAKE_TEMP_INIT	180

int asus_fg_porting(struct fg_chip *chip);
void asus_set_battery_version(void);
void asus_check_batt_id(struct fg_chip *chip);

extern struct fg_chip *g_fgChip;
extern bool g_charger_mode;
extern int fake_temp;


#define CYCLE_COUNT_DATA_MAGIC  0x85
#define CYCLE_COUNT_FILE_NAME   "/dev/block/bootdevice/by-name/batinfo"
#define Charging		0
#define DisCharging		1

/* Cycle Count Date Structure saved in emmc
 * magic - magic number for data verification
 * charge_cap_accum - Accumulated charging capacity
 * charge_last_soc - last saved soc before reset/shutdown
 * [0]:battery_soc [1]:system_soc [2]:monotonic_soc
 */
struct CYCLE_COUNT_DATA{
	int magic;
	int charge_cap_accum[3];
	int charge_last_soc[3];
	unsigned long battery_total_time;
	unsigned long high_vol_total_time;
	unsigned long high_temp_total_time;
	unsigned long high_temp_vol_time;
	u32 reload_condition;
};

#define CYCLE_FULL_THRESH_DEFAULT   95 // 85% as one full cycle
#define CYCLE_SOC_FULL  0xFF
#define CYCLE_COUNT_WRITEBACK_THRESH  	25 // 9.8%
#define CYCLE_SYSTEM_SOC_REG		0x574
#define CYCLE_SYSTEM_SOC_OFFSET	0
#define CYCLE_MONO_SOC_REG		0x574
#define CYCLE_MONO_SOC_OFFSET	2
#define FILE_OP_READ   0
#define FILE_OP_WRITE   1
#define CYCLE_COUNT_DATA_OFFSET  0x0

enum inde_of_record{
	RECORD_RCONN,
	RECORD_CHARGEFULL,
	RECORD_PENDINGFULL,
};

struct RECORD_DATA{
	int magic;
	int pos;
	int value;
};

#define ASUS_REPORT_FULL_IBAT_THRESH    (-400000)// 400mA
#define ASUS_REPORT_FULL_DEBOUNCE_TIME  20// sec

int asus_fg_get_record(struct RECORD_DATA *data);
int asus_fg_set_record(struct RECORD_DATA *data);
int asus_set_RCONN_RECORED(int val);
int asus_get_RCONN_RECORED(int *val);
int asus_get_record(int *val,int index);
int asus_set_record(int val,int index);
extern void asus_check_full_pending(struct fg_chip *chip, int ibatt_now, int msoc);

#endif
