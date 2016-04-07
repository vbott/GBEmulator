#pragma once
#include "GBEmulator.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>


uint8_t gl_bios[] = {
	0x31, 0xFE, 0xFF, 0xAF, 0x21, 0xFF, 0x9F, 0x32, 0xCB, 0x7C, 0x20, 0xFB, 0x21, 0x26, 0xFF, 0x0E,
	0x11, 0x3E, 0x80, 0x32, 0xE2, 0x0C, 0x3E, 0xF3, 0xE2, 0x32, 0x3E, 0x77, 0x77, 0x3E, 0xFC, 0xE0,
	0x47, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x1A, 0xCD, 0x95, 0x00, 0xCD, 0x96, 0x00, 0x13, 0x7B,
	0xFE, 0x34, 0x20, 0xF3, 0x11, 0xD8, 0x00, 0x06, 0x08, 0x1A, 0x13, 0x22, 0x23, 0x05, 0x20, 0xF9,
	0x3E, 0x19, 0xEA, 0x10, 0x99, 0x21, 0x2F, 0x99, 0x0E, 0x0C, 0x3D, 0x28, 0x08, 0x32, 0x0D, 0x20,
	0xF9, 0x2E, 0x0F, 0x18, 0xF3, 0x67, 0x3E, 0x64, 0x57, 0xE0, 0x42, 0x3E, 0x91, 0xE0, 0x40, 0x04,
	0x1E, 0x02, 0x0E, 0x0C, 0xF0, 0x44, 0xFE, 0x90, 0x20, 0xFA, 0x0D, 0x20, 0xF7, 0x1D, 0x20, 0xF2,
	0x0E, 0x13, 0x24, 0x7C, 0x1E, 0x83, 0xFE, 0x62, 0x28, 0x06, 0x1E, 0xC1, 0xFE, 0x64, 0x20, 0x06,
	0x7B, 0xE2, 0x0C, 0x3E, 0x87, 0xF2, 0xF0, 0x42, 0x90, 0xE0, 0x42, 0x15, 0x20, 0xD2, 0x05, 0x20,
	0x4F, 0x16, 0x20, 0x18, 0xCB, 0x4F, 0x06, 0x04, 0xC5, 0xCB, 0x11, 0x17, 0xC1, 0xCB, 0x11, 0x17,
	0x05, 0x20, 0xF5, 0x22, 0x23, 0x22, 0x23, 0xC9, 0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B,
	0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
	0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC,
	0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E, 0x3c, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x4C,
	0x21, 0x04, 0x01, 0x11, 0xA8, 0x00, 0x1A, 0x13, 0xBE, 0x20, 0xFE, 0x23, 0x7D, 0xFE, 0x34, 0x20,
	0xF5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20, 0xFB, 0x86, 0x20, 0xFE, 0x3E, 0x01, 0xE0, 0x50
};

typedef void (GBEmulator::CPU::*Ptr)();

Ptr	gl_ops[] = { 
	&GBEmulator::CPU::NOP,		&GBEmulator::CPU::LDBCnn,	&GBEmulator::CPU::LDBCmA,	&GBEmulator::CPU::INCBC,
	&GBEmulator::CPU::INCr_b,	&GBEmulator::CPU::DECr_b,	&GBEmulator::CPU::LDrn_b,	&GBEmulator::CPU::RLCA,
	&GBEmulator::CPU::LDmmSP,	&GBEmulator::CPU::ADDHLBC,	&GBEmulator::CPU::LDABCm,	&GBEmulator::CPU::DECBC,
	&GBEmulator::CPU::INCr_c,	&GBEmulator::CPU::DECr_c,	&GBEmulator::CPU::LDrn_c,	&GBEmulator::CPU::RRCA,
	// 10
	&GBEmulator::CPU::DJNZn,	&GBEmulator::CPU::LDDEnn,	&GBEmulator::CPU::LDDEmA,	&GBEmulator::CPU::INCDE,
	&GBEmulator::CPU::INCr_d,	&GBEmulator::CPU::DECr_d,	&GBEmulator::CPU::LDrn_d,	&GBEmulator::CPU::RLA,
	&GBEmulator::CPU::JRn,		&GBEmulator::CPU::ADDHLDE,	&GBEmulator::CPU::LDADEm,	&GBEmulator::CPU::DECDE,
	&GBEmulator::CPU::INCr_e,	&GBEmulator::CPU::DECr_e,	&GBEmulator::CPU::LDrn_e,	&GBEmulator::CPU::RRA,
	// 20
	&GBEmulator::CPU::JRNZn,	&GBEmulator::CPU::LDHLnn,	&GBEmulator::CPU::LDHLIA,	&GBEmulator::CPU::INCHL,
	&GBEmulator::CPU::INCr_h,	&GBEmulator::CPU::DECr_h,	&GBEmulator::CPU::LDrn_h,	&GBEmulator::CPU::DAA,
	&GBEmulator::CPU::JRZn,	&GBEmulator::CPU::ADDHLHL,	&GBEmulator::CPU::LDAHLI,	&GBEmulator::CPU::DECHL,
	&GBEmulator::CPU::INCr_l,	&GBEmulator::CPU::DECr_l,	&GBEmulator::CPU::LDrn_l,	&GBEmulator::CPU::CPL,
	// 30
	&GBEmulator::CPU::JRNCn,	&GBEmulator::CPU::LDSPnn,	&GBEmulator::CPU::LDHLDA,	&GBEmulator::CPU::INCSP,
	&GBEmulator::CPU::INCHLm,	&GBEmulator::CPU::DECHLm,	&GBEmulator::CPU::LDHLmn,	&GBEmulator::CPU::SCF,
	&GBEmulator::CPU::JRCn,	&GBEmulator::CPU::ADDHLSP,	&GBEmulator::CPU::LDAHLD,	&GBEmulator::CPU::DECSP,
	&GBEmulator::CPU::INCr_a,	&GBEmulator::CPU::DECr_a,	&GBEmulator::CPU::LDrn_a,	&GBEmulator::CPU::CCF,
	// 40
	&GBEmulator::CPU::LDrr_bb,	&GBEmulator::CPU::LDrr_bc,	&GBEmulator::CPU::LDrr_bd,	&GBEmulator::CPU::LDrr_be,
	&GBEmulator::CPU::LDrr_bh,	&GBEmulator::CPU::LDrr_bl,	&GBEmulator::CPU::LDrHLm_b,	&GBEmulator::CPU::LDrr_ba,
	&GBEmulator::CPU::LDrr_cb,	&GBEmulator::CPU::LDrr_cc,	&GBEmulator::CPU::LDrr_cd,	&GBEmulator::CPU::LDrr_ce,
	&GBEmulator::CPU::LDrr_ch,	&GBEmulator::CPU::LDrr_cl,	&GBEmulator::CPU::LDrHLm_c,	&GBEmulator::CPU::LDrr_ca,
	// 50
	&GBEmulator::CPU::LDrr_db,	&GBEmulator::CPU::LDrr_dc,	&GBEmulator::CPU::LDrr_dd,	&GBEmulator::CPU::LDrr_de,
	&GBEmulator::CPU::LDrr_dh,	&GBEmulator::CPU::LDrr_dl,	&GBEmulator::CPU::LDrHLm_d,	&GBEmulator::CPU::LDrr_da,
	&GBEmulator::CPU::LDrr_eb,	&GBEmulator::CPU::LDrr_ec,	&GBEmulator::CPU::LDrr_ed,	&GBEmulator::CPU::LDrr_ee,
	&GBEmulator::CPU::LDrr_eh,	&GBEmulator::CPU::LDrr_el,	&GBEmulator::CPU::LDrHLm_e,	&GBEmulator::CPU::LDrr_ea,
	// 60
	&GBEmulator::CPU::LDrr_hb,	&GBEmulator::CPU::LDrr_hc,	&GBEmulator::CPU::LDrr_hd,	&GBEmulator::CPU::LDrr_he,
	&GBEmulator::CPU::LDrr_hh,	&GBEmulator::CPU::LDrr_hl,	&GBEmulator::CPU::LDrHLm_h,	&GBEmulator::CPU::LDrr_ha,
	&GBEmulator::CPU::LDrr_lb,	&GBEmulator::CPU::LDrr_lc,	&GBEmulator::CPU::LDrr_ld,	&GBEmulator::CPU::LDrr_le,
	&GBEmulator::CPU::LDrr_lh,	&GBEmulator::CPU::LDrr_ll,	&GBEmulator::CPU::LDrHLm_l,	&GBEmulator::CPU::LDrr_la,
	// 70
	&GBEmulator::CPU::LDHLmr_b,	&GBEmulator::CPU::LDHLmr_c,	&GBEmulator::CPU::LDHLmr_d,	&GBEmulator::CPU::LDHLmr_e,
	&GBEmulator::CPU::LDHLmr_h,	&GBEmulator::CPU::LDHLmr_l,	&GBEmulator::CPU::HALT,		&GBEmulator::CPU::LDHLmr_a,
	&GBEmulator::CPU::LDrr_ab,	&GBEmulator::CPU::LDrr_ac,	&GBEmulator::CPU::LDrr_ad,	&GBEmulator::CPU::LDrr_ae,
	&GBEmulator::CPU::LDrr_ah,	&GBEmulator::CPU::LDrr_al,	&GBEmulator::CPU::LDrHLm_a,	&GBEmulator::CPU::LDrr_aa,
	// 80
	&GBEmulator::CPU::ADDr_b,	&GBEmulator::CPU::ADDr_c,	&GBEmulator::CPU::ADDr_d,	&GBEmulator::CPU::ADDr_e,
	&GBEmulator::CPU::ADDr_h,	&GBEmulator::CPU::ADDr_l,	&GBEmulator::CPU::ADDHL,		&GBEmulator::CPU::ADDr_a,
	&GBEmulator::CPU::ADCr_b,	&GBEmulator::CPU::ADCr_c,	&GBEmulator::CPU::ADCr_d,	&GBEmulator::CPU::ADCr_e,
	&GBEmulator::CPU::ADCr_h,	&GBEmulator::CPU::ADCr_l,	&GBEmulator::CPU::ADCHL,		&GBEmulator::CPU::ADCr_a,
	// 90
	&GBEmulator::CPU::SUBr_b,	&GBEmulator::CPU::SUBr_c,	&GBEmulator::CPU::SUBr_d,	&GBEmulator::CPU::SUBr_e,
	&GBEmulator::CPU::SUBr_h,	&GBEmulator::CPU::SUBr_l,	&GBEmulator::CPU::SUBHL,		&GBEmulator::CPU::SUBr_a,
	&GBEmulator::CPU::SBCr_b,	&GBEmulator::CPU::SBCr_c,	&GBEmulator::CPU::SBCr_d,	&GBEmulator::CPU::SBCr_e,
	&GBEmulator::CPU::SBCr_h,	&GBEmulator::CPU::SBCr_l,	&GBEmulator::CPU::SBCHL,		&GBEmulator::CPU::SBCr_a,
	// A0
	&GBEmulator::CPU::ANDr_b,	&GBEmulator::CPU::ANDr_c,	&GBEmulator::CPU::ANDr_d,	&GBEmulator::CPU::ANDr_e,
	&GBEmulator::CPU::ANDr_h,	&GBEmulator::CPU::ANDr_l,	&GBEmulator::CPU::ANDHL,		&GBEmulator::CPU::ANDr_a,
	&GBEmulator::CPU::XORr_b,	&GBEmulator::CPU::XORr_c,	&GBEmulator::CPU::XORr_d,	&GBEmulator::CPU::XORr_e,
	&GBEmulator::CPU::XORr_h,	&GBEmulator::CPU::XORr_l,	&GBEmulator::CPU::XORHL,		&GBEmulator::CPU::XORr_a,
	// B0
	&GBEmulator::CPU::ORr_b,	&GBEmulator::CPU::ORr_c,		&GBEmulator::CPU::ORr_d,		&GBEmulator::CPU::ORr_e,
	&GBEmulator::CPU::ORr_h,	&GBEmulator::CPU::ORr_l,		&GBEmulator::CPU::ORHL,		&GBEmulator::CPU::ORr_a,
	&GBEmulator::CPU::CPr_b,	&GBEmulator::CPU::CPr_c,		&GBEmulator::CPU::CPr_d,		&GBEmulator::CPU::CPr_e,
	&GBEmulator::CPU::CPr_h,	&GBEmulator::CPU::CPr_l,		&GBEmulator::CPU::CPHL,		&GBEmulator::CPU::CPr_a,
	// C0
	&GBEmulator::CPU::RETNZ,	&GBEmulator::CPU::POPBC,		&GBEmulator::CPU::JPNZnn,	&GBEmulator::CPU::JPnn,
	&GBEmulator::CPU::CALLNZnn,	&GBEmulator::CPU::PUSHBC,	&GBEmulator::CPU::ADDn,		&GBEmulator::CPU::RST00,
	&GBEmulator::CPU::RETZ,	&GBEmulator::CPU::RET,		&GBEmulator::CPU::JPZnn,		&GBEmulator::CPU::MAPcb,
	&GBEmulator::CPU::CALLZnn,	&GBEmulator::CPU::CALLnn,	&GBEmulator::CPU::ADCn,		&GBEmulator::CPU::RST08,
	// D0
	&GBEmulator::CPU::RETNC,	&GBEmulator::CPU::POPDE,		&GBEmulator::CPU::JPNCnn,	&GBEmulator::CPU::undefined,
	&GBEmulator::CPU::CALLNCnn,	&GBEmulator::CPU::PUSHDE,	&GBEmulator::CPU::SUBn,		&GBEmulator::CPU::RST10,
	&GBEmulator::CPU::RETC,	&GBEmulator::CPU::RETI,		&GBEmulator::CPU::JPCnn,		&GBEmulator::CPU::undefined,
	&GBEmulator::CPU::CALLCnn,	&GBEmulator::CPU::undefined,		&GBEmulator::CPU::SBCn,		&GBEmulator::CPU::RST18,
	// E0
	&GBEmulator::CPU::LDIOnA,	&GBEmulator::CPU::POPHL,		&GBEmulator::CPU::LDIOCA,	&GBEmulator::CPU::undefined,
	&GBEmulator::CPU::undefined,		&GBEmulator::CPU::PUSHHL,	&GBEmulator::CPU::ANDn,		&GBEmulator::CPU::RST20,
	&GBEmulator::CPU::ADDSPn,	&GBEmulator::CPU::JPHL,		&GBEmulator::CPU::LDmmA,		&GBEmulator::CPU::undefined,
	&GBEmulator::CPU::undefined,		&GBEmulator::CPU::undefined,		&GBEmulator::CPU::XORn,		&GBEmulator::CPU::RST28,
	// F0
	&GBEmulator::CPU::LDAIOn,	&GBEmulator::CPU::POPAF,		&GBEmulator::CPU::LDAIOC,	&GBEmulator::CPU::DI,
	&GBEmulator::CPU::undefined,		&GBEmulator::CPU::PUSHAF,	&GBEmulator::CPU::ORn,		&GBEmulator::CPU::RST30,
	&GBEmulator::CPU::LDHLSPn,	&GBEmulator::CPU::undefined,		&GBEmulator::CPU::LDAmm,		&GBEmulator::CPU::EI,
	&GBEmulator::CPU::undefined,		&GBEmulator::CPU::undefined,		&GBEmulator::CPU::CPn,		&GBEmulator::CPU::RST38
};

Ptr gl_dops[] = {
	&GBEmulator::CPU::RLCr_b,	&GBEmulator::CPU::RLCr_c,	&GBEmulator::CPU::RLCr_d,	&GBEmulator::CPU::RLCr_e,
	&GBEmulator::CPU::RLCr_h,	&GBEmulator::CPU::RLCr_l,	&GBEmulator::CPU::RLCHL,		&GBEmulator::CPU::RLCr_a,
	&GBEmulator::CPU::RRCr_b,	&GBEmulator::CPU::RRCr_c,	&GBEmulator::CPU::RRCr_d,	&GBEmulator::CPU::RRCr_e,
	&GBEmulator::CPU::RRCr_h,	&GBEmulator::CPU::RRCr_l,	&GBEmulator::CPU::RRCHL,		&GBEmulator::CPU::RRCr_a,
	// CB10
	&GBEmulator::CPU::RLr_b,	&GBEmulator::CPU::RLr_c,		&GBEmulator::CPU::RLr_d,		&GBEmulator::CPU::RLr_e,
	&GBEmulator::CPU::RLr_h,	&GBEmulator::CPU::RLr_l,		&GBEmulator::CPU::RLHL,		&GBEmulator::CPU::RLr_a,
	&GBEmulator::CPU::RRr_b,	&GBEmulator::CPU::RRr_c,		&GBEmulator::CPU::RRr_d,		&GBEmulator::CPU::RRr_e,
	&GBEmulator::CPU::RRr_h,	&GBEmulator::CPU::RRr_l,		&GBEmulator::CPU::RRHL,		&GBEmulator::CPU::RRr_a,
	// CB20
	&GBEmulator::CPU::SLAr_b,	&GBEmulator::CPU::SLAr_c,	&GBEmulator::CPU::SLAr_d,	&GBEmulator::CPU::SLAr_e,
	&GBEmulator::CPU::SLAr_h,	&GBEmulator::CPU::SLAr_l,	&GBEmulator::CPU::undefined,		&GBEmulator::CPU::SLAr_a,
	&GBEmulator::CPU::SRAr_b,	&GBEmulator::CPU::SRAr_c,	&GBEmulator::CPU::SRAr_d,	&GBEmulator::CPU::SRAr_e,
	&GBEmulator::CPU::SRAr_h,	&GBEmulator::CPU::SRAr_l,	&GBEmulator::CPU::undefined,		&GBEmulator::CPU::SRAr_a,
	// CB30
	&GBEmulator::CPU::SWAPr_b,	&GBEmulator::CPU::SWAPr_c,	&GBEmulator::CPU::SWAPr_d,	&GBEmulator::CPU::SWAPr_e,
	&GBEmulator::CPU::SWAPr_h,	&GBEmulator::CPU::SWAPr_l,	&GBEmulator::CPU::undefined,		&GBEmulator::CPU::SWAPr_a,
	&GBEmulator::CPU::SRLr_b,	&GBEmulator::CPU::SRLr_c,	&GBEmulator::CPU::SRLr_d,	&GBEmulator::CPU::SRLr_e,
	&GBEmulator::CPU::SRLr_h,	&GBEmulator::CPU::SRLr_l,	&GBEmulator::CPU::undefined,		&GBEmulator::CPU::SRLr_a,
	// CB40
	&GBEmulator::CPU::BIT0b,	&GBEmulator::CPU::BIT0c,		&GBEmulator::CPU::BIT0d,		&GBEmulator::CPU::BIT0e,
	&GBEmulator::CPU::BIT0h,	&GBEmulator::CPU::BIT0l,		&GBEmulator::CPU::BIT0m,		&GBEmulator::CPU::BIT0a,
	&GBEmulator::CPU::BIT1b,	&GBEmulator::CPU::BIT1c,		&GBEmulator::CPU::BIT1d,		&GBEmulator::CPU::BIT1e,
	&GBEmulator::CPU::BIT1h,	&GBEmulator::CPU::BIT1l,		&GBEmulator::CPU::BIT1m,		&GBEmulator::CPU::BIT1a,
	// CB50
	&GBEmulator::CPU::BIT2b,	&GBEmulator::CPU::BIT2c,		&GBEmulator::CPU::BIT2d,		&GBEmulator::CPU::BIT2e,
	&GBEmulator::CPU::BIT2h,	&GBEmulator::CPU::BIT2l,		&GBEmulator::CPU::BIT2m,		&GBEmulator::CPU::BIT2a,
	&GBEmulator::CPU::BIT3b,	&GBEmulator::CPU::BIT3c,		&GBEmulator::CPU::BIT3d,		&GBEmulator::CPU::BIT3e,
	&GBEmulator::CPU::BIT3h,	&GBEmulator::CPU::BIT3l,		&GBEmulator::CPU::BIT3m,		&GBEmulator::CPU::BIT3a,
	// CB60
	&GBEmulator::CPU::BIT4b,	&GBEmulator::CPU::BIT4c,		&GBEmulator::CPU::BIT4d,		&GBEmulator::CPU::BIT4e,
	&GBEmulator::CPU::BIT4h,	&GBEmulator::CPU::BIT4l,		&GBEmulator::CPU::BIT4m,		&GBEmulator::CPU::BIT4a,
	&GBEmulator::CPU::BIT5b,	&GBEmulator::CPU::BIT5c,		&GBEmulator::CPU::BIT5d,		&GBEmulator::CPU::BIT5e,
	&GBEmulator::CPU::BIT5h,	&GBEmulator::CPU::BIT5l,		&GBEmulator::CPU::BIT5m,		&GBEmulator::CPU::BIT5a,
	// CB70
	&GBEmulator::CPU::BIT6b,	&GBEmulator::CPU::BIT6c,		&GBEmulator::CPU::BIT6d,		&GBEmulator::CPU::BIT6e,
	&GBEmulator::CPU::BIT6h,	&GBEmulator::CPU::BIT6l,		&GBEmulator::CPU::BIT6m,		&GBEmulator::CPU::BIT6a,
	&GBEmulator::CPU::BIT7b,	&GBEmulator::CPU::BIT7c,		&GBEmulator::CPU::BIT7d,		&GBEmulator::CPU::BIT7e,
	&GBEmulator::CPU::BIT7h,	&GBEmulator::CPU::BIT7l,		&GBEmulator::CPU::BIT7m,		&GBEmulator::CPU::BIT7a,
	// CB80
	&GBEmulator::CPU::RES0b,	&GBEmulator::CPU::RES0c,		&GBEmulator::CPU::RES0d,		&GBEmulator::CPU::RES0e,
	&GBEmulator::CPU::RES0h,	&GBEmulator::CPU::RES0l,		&GBEmulator::CPU::RES0m,		&GBEmulator::CPU::RES0a,
	&GBEmulator::CPU::RES1b,	&GBEmulator::CPU::RES1c,		&GBEmulator::CPU::RES1d,		&GBEmulator::CPU::RES1e,
	&GBEmulator::CPU::RES1h,	&GBEmulator::CPU::RES1l,		&GBEmulator::CPU::RES1m,		&GBEmulator::CPU::RES1a,
	// CB90
	&GBEmulator::CPU::RES2b,	&GBEmulator::CPU::RES2c,		&GBEmulator::CPU::RES2d,		&GBEmulator::CPU::RES2e,
	&GBEmulator::CPU::RES2h,	&GBEmulator::CPU::RES2l,		&GBEmulator::CPU::RES2m,		&GBEmulator::CPU::RES2a,
	&GBEmulator::CPU::RES3b,	&GBEmulator::CPU::RES3c,		&GBEmulator::CPU::RES3d,		&GBEmulator::CPU::RES3e,
	&GBEmulator::CPU::RES3h,	&GBEmulator::CPU::RES3l,		&GBEmulator::CPU::RES3m,		&GBEmulator::CPU::RES3a,
	// CBA0
	&GBEmulator::CPU::RES4b,	&GBEmulator::CPU::RES4c,		&GBEmulator::CPU::RES4d,		&GBEmulator::CPU::RES4e,
	&GBEmulator::CPU::RES4h,	&GBEmulator::CPU::RES4l,		&GBEmulator::CPU::RES4m,		&GBEmulator::CPU::RES4a,
	&GBEmulator::CPU::RES5b,	&GBEmulator::CPU::RES5c,		&GBEmulator::CPU::RES5d,		&GBEmulator::CPU::RES5e,
	&GBEmulator::CPU::RES5h,	&GBEmulator::CPU::RES5l,		&GBEmulator::CPU::RES5m,		&GBEmulator::CPU::RES5a,
	// CBB0
	&GBEmulator::CPU::RES6b,	&GBEmulator::CPU::RES6c,		&GBEmulator::CPU::RES6d,		&GBEmulator::CPU::RES6e,
	&GBEmulator::CPU::RES6h,	&GBEmulator::CPU::RES6l,		&GBEmulator::CPU::RES6m,		&GBEmulator::CPU::RES6a,
	&GBEmulator::CPU::RES7b,	&GBEmulator::CPU::RES7c,		&GBEmulator::CPU::RES7d,		&GBEmulator::CPU::RES7e,
	&GBEmulator::CPU::RES7h,	&GBEmulator::CPU::RES7l,		&GBEmulator::CPU::RES7m,		&GBEmulator::CPU::RES7a,
	// CBC0
	&GBEmulator::CPU::SET0b,	&GBEmulator::CPU::SET0c,		&GBEmulator::CPU::SET0d,		&GBEmulator::CPU::SET0e,
	&GBEmulator::CPU::SET0h,	&GBEmulator::CPU::SET0l,		&GBEmulator::CPU::SET0m,		&GBEmulator::CPU::SET0a,
	&GBEmulator::CPU::SET1b,	&GBEmulator::CPU::SET1c,		&GBEmulator::CPU::SET1d,		&GBEmulator::CPU::SET1e,
	&GBEmulator::CPU::SET1h,	&GBEmulator::CPU::SET1l,		&GBEmulator::CPU::SET1m,		&GBEmulator::CPU::SET1a,
	// CBD0
	&GBEmulator::CPU::SET2b,	&GBEmulator::CPU::SET2c,		&GBEmulator::CPU::SET2d,		&GBEmulator::CPU::SET2e,
	&GBEmulator::CPU::SET2h,	&GBEmulator::CPU::SET2l,		&GBEmulator::CPU::SET2m,		&GBEmulator::CPU::SET2a,
	&GBEmulator::CPU::SET3b,	&GBEmulator::CPU::SET3c,		&GBEmulator::CPU::SET3d,		&GBEmulator::CPU::SET3e,
	&GBEmulator::CPU::SET3h,	&GBEmulator::CPU::SET3l,		&GBEmulator::CPU::SET3m,		&GBEmulator::CPU::SET3a,
	// CBE0
	&GBEmulator::CPU::SET4b,	&GBEmulator::CPU::SET4c,		&GBEmulator::CPU::SET4d,		&GBEmulator::CPU::SET4e,
	&GBEmulator::CPU::SET4h,	&GBEmulator::CPU::SET4l,		&GBEmulator::CPU::SET4m,		&GBEmulator::CPU::SET4a,
	&GBEmulator::CPU::SET5b,	&GBEmulator::CPU::SET5c,		&GBEmulator::CPU::SET5d,		&GBEmulator::CPU::SET5e,
	&GBEmulator::CPU::SET5h,	&GBEmulator::CPU::SET5l,		&GBEmulator::CPU::SET5m,		&GBEmulator::CPU::SET5a,
	// CBF0
	&GBEmulator::CPU::SET6b,	&GBEmulator::CPU::SET6c,		&GBEmulator::CPU::SET6d,		&GBEmulator::CPU::SET6e,
	&GBEmulator::CPU::SET6h,	&GBEmulator::CPU::SET6l,		&GBEmulator::CPU::SET6m,		&GBEmulator::CPU::SET6a,
	&GBEmulator::CPU::SET7b,	&GBEmulator::CPU::SET7c,		&GBEmulator::CPU::SET7d,		&GBEmulator::CPU::SET7e,
	&GBEmulator::CPU::SET7h,	&GBEmulator::CPU::SET7l,		&GBEmulator::CPU::SET7m,		&GBEmulator::CPU::SET7a,
};

void Module::init()
{}

void Module::update()
{
}

GBEmulator::GBEmulator()
{
	_z80.reset();
	_z80.mmu.load("opus5.gb");
	_z80.reg.pc = 0x100; _z80.mmu.inbios = false; _z80.reg.sp = 0xFFFE; _z80.reg.c = 0x13; _z80.reg.e = 0xD8; _z80.reg.a = 1;
}

void GBEmulator::run()
{
	int			i = 1;

	while (_loop)
	{
		_modules[0]->update();

		auto fclk = _z80.clock.m + 17556;
		do
		{
			if (_z80.reg.halt)
				_z80.reg.m = 1;
			else
			{
				auto op = _z80.mmu.read8b(_z80.reg.pc++);
				(_z80.*gl_ops[op])();
				_z80.clock.m += _z80.reg.m;
				if (_z80.mmu.inbios && _z80.reg.pc == 0x0100)
					_z80.mmu.inbios = false;
			}
			_z80.gpu.modeclock += _z80.reg.m;
			i++;
			_z80.gpu.run();
		} while (_z80.clock.m < fclk);

		_modules[1]->update();
		//_sleep(20);
		//for (auto &module : _modules)
		//	module->update();
	}
}

void	GBEmulator::processInput(SDL_Event &ev)
{
	switch (ev.type)
	{
		case SDL_QUIT:
			_loop = false;
			break;
	}
}

int *GBEmulator::getPixels()
{
	return _z80.gpu.pixels;
}

void	GBEmulator::GPU::run()
{
	switch (mode)
	{
		// OAM read mode, scanline active
	case 2:
		if (modeclock >= 20)
		{
			// Enter scanline mode 3
			modeclock = 0;
			mode = 3;
		}
		break;

		// VRAM read mode, scanline active
		// Treat end of mode 3 as end of scanline
	case 3:
		if (modeclock >= 43)
		{
			// Enter hblank
			modeclock = 0;
			mode = 0;

			// Write a scanline to the framebuffer
			renderscan();
		}
		break;

		// Hblank
		// After the last hblank, push the screen data to canvas
	case 0:
		if (modeclock >= 51)
		{
			modeclock = 0;
			line++;

			if (line == 143)
			{
				// Enter vblank
				mode = 1;
				//GPU._canvas.putImageData(GPU._scrn, 0, 0);
			}
			else
			{
				mode = 2;
			}
		}
		break;

		// Vblank (10 lines)
	case 1:
		if (modeclock >= 114)
		{
			modeclock = 0;
			line++;

			if (line > 153)
			{
				// Restart scanning modes
				mode = 2;
				line = 0;
			}
		}
		break;
	}
}

void	GBEmulator::GPU::renderscan()
{
	// VRAM offset for the tile map
	int mapoffs = bgmap ? 0x1C00 : 0x1800;

	// Which line of tiles to use in the map
	mapoffs += ((line + scy) & 255) >> 3;

	// Which tile to start with in the map line
	int lineoffs = (scx >> 3);

	// Which line of pixels to use in the tiles
	int y = (line + scy) & 7;

	// Where in the tileline to start
	int x = scx & 7;

	// Where to render on the canvas
	int canvasoffs = line * 160 * 4;

	// Read tile index from the background map
	int tile = vram[mapoffs + lineoffs];

	// If the tile data set in use is #1, the
	// indices are signed; calculate a real tile offset
	if (bgtile == 1 && tile < 128)
		tile += 256;

	for (int i = 0; i < 160; i++)
	{
		// Re-map the tile pixel through the palette
		auto colour = pal[tileset[tile][y][x]];

		// Plot the pixel to canvas
		auto data = (uint8_t*)pixels;
		data[canvasoffs + 0] = colour[0];
		data[canvasoffs + 1] = colour[1];
		data[canvasoffs + 2] = colour[2];
		data[canvasoffs + 3] = colour[3];
		canvasoffs += 4;

		// When this tile ends, read another
		x++;
		if (x == 8)
		{
			x = 0;
			lineoffs = (lineoffs + 1) & 31;
			tile = vram[mapoffs + lineoffs];
			if (bgtile == 1 && tile < 128) tile += 256;
		}
	}
}

uint8_t GBEmulator::GPU::read(uint16_t addr)
{
	switch (addr)
	{
		// LCD Control
	case 0xFF40:
		return (switchbg ? 0x01 : 0x00) |
			(bgmap ? 0x08 : 0x00) |
			(bgtile ? 0x10 : 0x00) |
			(switchlcd ? 0x80 : 0x00);

		// Scroll Y
	case 0xFF42:
		return scy;

		// Scroll X
	case 0xFF43:
		return scx;

		// Current scanline
	case 0xFF44:
		return line;
	}
}

void	GBEmulator::GPU::write(uint16_t addr, uint8_t val)
{
	switch (addr)
	{
		// LCD Control
	case 0xFF40:
		switchbg = (val & 0x01) ? true : false;
		bgmap = (val & 0x08) ? true : false;
		bgtile = (val & 0x10) ? true : false;
		switchlcd = (val & 0x80) ? true : false;
		break;

		// Scroll Y
	case 0xFF42:
		scy = val;
		break;

		// Scroll X
	case 0xFF43:
		scx = val;
		break;

		// Background palette
	case 0xFF47:
		for (int i = 0; i < 4; i++)
		{
			switch ((val >> (i * 2)) & 3)
			{
				case 0: pal[i][0] = 255;
						pal[i][1] = 255;
						pal[i][2] = 255;
						pal[i][3] = 255;
						break;
				case 1: pal[i][0] = 192;
						pal[i][1] = 192;
						pal[i][2] = 192;
						pal[i][3] = 255;
						break;
				case 2: pal[i][0] = 96;
						pal[i][1] = 96;
						pal[i][2] = 96;
						pal[i][3] = 255;
						break;
				case 3: pal[i][0] = 0;
						pal[i][1] = 0;
						pal[i][2] = 0;
						pal[i][3] = 255;
						break;
			}
		}
		break;
	}
}

void	GBEmulator::GPU::updatetile(uint16_t addr, uint8_t val)
{
	addr &= 0x1FFE;

	// Work out which tile and row was updated
	int tile = ((addr >> 4) & 511);
	int y = (addr >> 1) & 7;

	int sx;
	for (int x = 0; x < 8 && tile < 384; x++)
	{
		// Find bit index for this pixel
		sx = 1 << (7 - x);

		// Update tile set
		tileset[tile][y][x] =
			((vram[addr] & sx) ? 1 : 0) +
			((vram[addr + 1] & sx) ? 2 : 0);
	}
}

void	GBEmulator::CPU::reset()
{
	::memset(this, 0, sizeof(*this));
	mmu.bios = (uint8_t*)&gl_bios;
	mmu.inbios = true;
	mmu.gpu = &gpu;
}

void	GBEmulator::CPU::undefined()
{
	std::cout << "undefined op" << std::endl;
}

void	GBEmulator::CPU::MAPcb()
{
	auto i = mmu.read8b(reg.pc); reg.pc++;
	//reg.pc &= 65535;
	(this->*gl_dops[i])();
}

void	GBEmulator::MMU::load(std::string path)
{
	std::ifstream		file(path, std::ios::binary);

	if (file.is_open())
	{
		std::string		buffer;

		file.seekg(0, std::ios_base::end);
		auto	size = file.tellg();
		file.seekg(0, std::ios_base::beg);

		buffer.resize(size);
		file.read(const_cast<char*>(buffer.data()), size);
		::memcpy(rom, buffer.data(), std::min(size_t(32 * 1024), buffer.size()));
		file.close();
	}
}

uint8_t GBEmulator::MMU::read8b(uint16_t addr)
{
	switch (addr & 0xF000)
	{
		// BIOS (256b)/ROM0
	case 0x0000:
		if (inbios)
		{
			if (addr < 0x0100)
				return bios[addr];
		}

		return rom[addr];

		// ROM0
	case 0x1000:
	case 0x2000:
	case 0x3000:
		return rom[addr];

		// ROM1 (unbanked) (16k)
	case 0x4000:
	case 0x5000:
	case 0x6000:
	case 0x7000:
		return rom[addr];

		// Graphics: VRAM (8k)
	case 0x8000:
	case 0x9000:
		return gpu->vram[addr & 0x1FFF];

		// External RAM (8k)
	case 0xA000:
	case 0xB000:
		return eram[addr & 0x1FFF];

		// Working RAM (8k)
	case 0xC000:
	case 0xD000:
		return wram[addr & 0x1FFF];

		// Working RAM shadow
	case 0xE000:
		return wram[addr & 0x1FFF];

		// Working RAM shadow, I/O, Zero-page RAM
	case 0xF000:
		switch (addr & 0x0F00)
		{
			// Working RAM shadow
		case 0x000: case 0x100: case 0x200: case 0x300:
		case 0x400: case 0x500: case 0x600: case 0x700:
		case 0x800: case 0x900: case 0xA00: case 0xB00:
		case 0xC00: case 0xD00:
			return wram[addr & 0x1FFF];

			// Graphics: object attribute memory
			// OAM is 160 bytes, remaining bytes read as 0
		case 0xE00:
			if (addr < 0xFEA0)
				return gpu->oam[addr & 0xFF];
			else
				return 0;

			// Zero-page
		case 0xF00:
			if (addr >= 0xFF80)
			{
				return zram[addr & 0x7F];
			}
			else
			{
				// I/O control handling
				switch (addr & 0x00F0)
				{
					// GPU (64 registers)
					case 0x40: case 0x50: case 0x60: case 0x70:
						return gpu->read(addr);
				}
				return 0;
			}
		}
	}
}

uint16_t GBEmulator::MMU::read16b(uint16_t addr)
{
	return this->read8b(addr) + (this->read8b(addr + 1) << 8);
}

uint8_t GBEmulator::MMU::write8b(uint16_t addr, uint8_t val)
{
	switch (addr & 0xF000)
	{
		// BIOS (256b)/ROM0
	case 0x0000:
		if (inbios && addr < 0x0100)
				return 0;
		// ROM0
	case 0x1000:
	case 0x2000:
	case 0x3000:
		// ROM1 (unbanked) (16k)
	case 0x4000:
	case 0x5000:
	case 0x6000:
	case 0x7000:
		return 0;

		// Graphics: VRAM (8k)
	case 0x8000:
	case 0x9000:
		gpu->vram[addr & 0x1FFF] = val;
		gpu->updatetile(addr, val);
		return 0;

		// External RAM (8k)
	case 0xA000:
	case 0xB000:
		return eram[addr & 0x1FFF] = val;

		// Working RAM (8k)
	case 0xC000:
	case 0xD000:
		return wram[addr & 0x1FFF] = val;

		// Working RAM shadow
	case 0xE000:
		return wram[addr & 0x1FFF] = val;

		// Working RAM shadow, I/O, Zero-page RAM
	case 0xF000:
		switch (addr & 0x0F00)
		{
			// Working RAM shadow
		case 0x000: case 0x100: case 0x200: case 0x300:
		case 0x400: case 0x500: case 0x600: case 0x700:
		case 0x800: case 0x900: case 0xA00: case 0xB00:
		case 0xC00: case 0xD00:
			return wram[addr & 0x1FFF] = val;

			// Graphics: object attribute memory
			// OAM is 160 bytes, remaining bytes read as 0
		case 0xE00:
			if (addr < 0xFEA0)
				return gpu->oam[addr & 0xFF] = val;
			else
				return 0;

			// Zero-page
		case 0xF00:
			if (addr >= 0xFF80)
				return zram[addr & 0x7F] = val;
			else
			{
				// I/O control handling
				// Currently unhandled
				switch (addr & 0x00F0)
				{
					// GPU
					case 0x40: case 0x50: case 0x60: case 0x70:
						gpu->write(addr, val);
					return 0;
				}

				return 0;
			}
		}
	}
}

void GBEmulator::MMU::write16b(uint16_t addr, uint16_t val)
{
	write8b(addr, (uint8_t)(val & 0xFF));
	write8b(addr + 1, (uint8_t)(val >> 8));
}
