#pragma once
#include <vector>
#include <memory>
#include <limits>
#include <SDL.h>

class Module
{
public:
		virtual void init();
		virtual void update();
};

class GBEmulator
{
public:
	GBEmulator();

	struct GPU
	{
		void run();
		void renderscan();
		uint8_t read(uint16_t addr);
		void	write(uint16_t addr, uint8_t val);
		void	updatetile(uint16_t addr, uint8_t val);

		int		pixels[160 * 144];
		uint8_t	vram[8 * 1024];
		uint8_t	oam[256];

		uint8_t mode = 0;
		uint8_t modeclock = 0;
		uint8_t line = 0;
		uint8_t scx = 0;
		uint8_t scy = 0;
		bool switchbg = false;
		bool bgmap = false;
		bool bgtile = false;
		bool switchlcd = false;

		uint8_t pal[4][4];
		uint8_t tileset[384][8][8];
	};

	struct MMU 
	{
		void	load(std::string path);
		uint8_t read8b(uint16_t addr);
		uint16_t read16b(uint16_t addr);

		void	write16b(uint16_t addr, uint16_t val);
		uint8_t	write8b(uint16_t addr, uint8_t val);

		bool	inbios = true;
		uint8_t	const *bios;
		uint8_t	rom[32 * 1024];
		uint8_t	wram[8 * 1024];
		uint8_t	eram[8 * 1024];
		uint8_t	zram[128];

		//GPU
		GPU		*gpu;
	};

	struct CPU
	{
		struct
		{
			int			m = 0;
		} clock;

		struct
		{
			uint8_t		a = 0;
			uint8_t		b = 0;
			uint8_t		c = 0;
			uint8_t		d = 0;
			uint8_t		e = 0;
			uint8_t		h = 0;
			uint8_t		l = 0;
			uint8_t		f = 0;

			uint16_t	pc = 0;
			uint16_t	sp = 0;

			int			m = 0;
			bool		ime = false;
			bool		halt = false;
		} reg;

		MMU mmu;
		GPU gpu;

		void reset();
		void undefined();
		void MAPcb();
		void fz(int i, int as = 0) { reg.f = 0; if (!(i & 255)) reg.f |= 128; reg.f |= as ? 0x40 : 0; }

		void LDrr_bb() { reg.b = reg.b; reg.m = 1;  };
		void LDrr_bc() { reg.b = reg.c; reg.m = 1;  };
		void LDrr_bd() { reg.b = reg.d; reg.m = 1;  };
		void LDrr_be() { reg.b = reg.e; reg.m = 1;  };
		void LDrr_bh() { reg.b = reg.h; reg.m = 1;  };
		void LDrr_bl() { reg.b = reg.l; reg.m = 1;  };
		void LDrr_ba() { reg.b = reg.a; reg.m = 1;  };
		void LDrr_cb() { reg.c = reg.b; reg.m = 1;  };
		void LDrr_cc() { reg.c = reg.c; reg.m = 1;  };
		void LDrr_cd() { reg.c = reg.d; reg.m = 1;  };
		void LDrr_ce() { reg.c = reg.e; reg.m = 1;  };
		void LDrr_ch() { reg.c = reg.h; reg.m = 1;  };
		void LDrr_cl() { reg.c = reg.l; reg.m = 1;  };
		void LDrr_ca() { reg.c = reg.a; reg.m = 1;  };
		void LDrr_db() { reg.d = reg.b; reg.m = 1;  };
		void LDrr_dc() { reg.d = reg.c; reg.m = 1;  };
		void LDrr_dd() { reg.d = reg.d; reg.m = 1;  };
		void LDrr_de() { reg.d = reg.e; reg.m = 1;  };
		void LDrr_dh() { reg.d = reg.h; reg.m = 1;  };
		void LDrr_dl() { reg.d = reg.l; reg.m = 1;  };
		void LDrr_da() { reg.d = reg.a; reg.m = 1;  };
		void LDrr_eb() { reg.e = reg.b; reg.m = 1;  };
		void LDrr_ec() { reg.e = reg.c; reg.m = 1;  };
		void LDrr_ed() { reg.e = reg.d; reg.m = 1;  };
		void LDrr_ee() { reg.e = reg.e; reg.m = 1;  };
		void LDrr_eh() { reg.e = reg.h; reg.m = 1;  };
		void LDrr_el() { reg.e = reg.l; reg.m = 1;  };
		void LDrr_ea() { reg.e = reg.a; reg.m = 1;  };
		void LDrr_hb() { reg.h = reg.b; reg.m = 1;  };
		void LDrr_hc() { reg.h = reg.c; reg.m = 1;  };
		void LDrr_hd() { reg.h = reg.d; reg.m = 1;  };
		void LDrr_he() { reg.h = reg.e; reg.m = 1;  };
		void LDrr_hh() { reg.h = reg.h; reg.m = 1;  };
		void LDrr_hl() { reg.h = reg.l; reg.m = 1;  };
		void LDrr_ha() { reg.h = reg.a; reg.m = 1;  };
		void LDrr_lb() { reg.l = reg.b; reg.m = 1;  };
		void LDrr_lc() { reg.l = reg.c; reg.m = 1;  };
		void LDrr_ld() { reg.l = reg.d; reg.m = 1;  };
		void LDrr_le() { reg.l = reg.e; reg.m = 1;  };
		void LDrr_lh() { reg.l = reg.h; reg.m = 1;  };
		void LDrr_ll() { reg.l = reg.l; reg.m = 1;  };
		void LDrr_la() { reg.l = reg.a; reg.m = 1;  };
		void LDrr_ab() { reg.a = reg.b; reg.m = 1;  };
		void LDrr_ac() { reg.a = reg.c; reg.m = 1;  };
		void LDrr_ad() { reg.a = reg.d; reg.m = 1;  };
		void LDrr_ae() { reg.a = reg.e; reg.m = 1;  };
		void LDrr_ah() { reg.a = reg.h; reg.m = 1;  };
		void LDrr_al() { reg.a = reg.l; reg.m = 1;  };
		void LDrr_aa() { reg.a = reg.a; reg.m = 1;  };

		void LDrHLm_b() { reg.b = mmu.read8b((reg.h << 8) + reg.l); reg.m = 2;  };
		void LDrHLm_c () { reg.c = mmu.read8b((reg.h << 8) + reg.l); reg.m = 2;  };
		void LDrHLm_d () { reg.d = mmu.read8b((reg.h << 8) + reg.l); reg.m = 2;  };
		void LDrHLm_e () { reg.e = mmu.read8b((reg.h << 8) + reg.l); reg.m = 2;  };
		void LDrHLm_h () { reg.h = mmu.read8b((reg.h << 8) + reg.l); reg.m = 2;  };
		void LDrHLm_l () { reg.l = mmu.read8b((reg.h << 8) + reg.l); reg.m = 2;  };
		void LDrHLm_a () { reg.a = mmu.read8b((reg.h << 8) + reg.l); reg.m = 2;  };

		void LDHLmr_b () { mmu.write8b((reg.h << 8) + reg.l, reg.b); reg.m = 2;  };
		void LDHLmr_c () { mmu.write8b((reg.h << 8) + reg.l, reg.c); reg.m = 2;  };
		void LDHLmr_d () { mmu.write8b((reg.h << 8) + reg.l, reg.d); reg.m = 2;  };
		void LDHLmr_e () { mmu.write8b((reg.h << 8) + reg.l, reg.e); reg.m = 2;  };
		void LDHLmr_h () { mmu.write8b((reg.h << 8) + reg.l, reg.h); reg.m = 2;  };
		void LDHLmr_l () { mmu.write8b((reg.h << 8) + reg.l, reg.l); reg.m = 2;  };
		void LDHLmr_a () { mmu.write8b((reg.h << 8) + reg.l, reg.a); reg.m = 2;  };

		void LDrn_b () { reg.b = mmu.read8b(reg.pc); reg.pc++; reg.m = 2;  };
		void LDrn_c () { reg.c = mmu.read8b(reg.pc); reg.pc++; reg.m = 2;  };
		void LDrn_d () { reg.d = mmu.read8b(reg.pc); reg.pc++; reg.m = 2;  };
		void LDrn_e () { reg.e = mmu.read8b(reg.pc); reg.pc++; reg.m = 2;  };
		void LDrn_h () { reg.h = mmu.read8b(reg.pc); reg.pc++; reg.m = 2;  };
		void LDrn_l () { reg.l = mmu.read8b(reg.pc); reg.pc++; reg.m = 2;  };
		void LDrn_a () { reg.a = mmu.read8b(reg.pc); reg.pc++; reg.m = 2;  };


		void LDHLmn() { mmu.write8b((reg.h << 8) + reg.l, mmu.read8b(reg.pc)); reg.pc++; reg.m = 3;  };

		void LDBCmA () { mmu.write8b((reg.b << 8) + reg.c, reg.a); reg.m = 2;  };
		void LDDEmA () { mmu.write8b((reg.d << 8) + reg.e, reg.a); reg.m = 2;  };

		void LDmmA () { mmu.write8b(mmu.read16b(reg.pc), reg.a); reg.pc += 2; reg.m = 4;  };

		void LDABCm () { reg.a = mmu.read8b((reg.b << 8) + reg.c); reg.m = 2;  };
		void LDADEm () { reg.a = mmu.read8b((reg.d << 8) + reg.e); reg.m = 2;  };

		void LDAmm () { reg.a = mmu.read8b(mmu.read16b(reg.pc)); reg.pc += 2; reg.m = 4;  };

		void LDBCnn () { reg.c = mmu.read8b(reg.pc); reg.b = mmu.read8b(reg.pc + 1); reg.pc += 2; reg.m = 3;  };
		void LDDEnn () { reg.e = mmu.read8b(reg.pc); reg.d = mmu.read8b(reg.pc + 1); reg.pc += 2; reg.m = 3;  };
		void LDHLnn () { reg.l = mmu.read8b(reg.pc); reg.h = mmu.read8b(reg.pc + 1); reg.pc += 2; reg.m = 3;  };
		void LDSPnn () { reg.sp = mmu.read16b(reg.pc); reg.pc += 2; reg.m = 3;  };

		void LDHLmm () { auto i = mmu.read16b(reg.pc); reg.pc += 2; reg.l = mmu.read8b(i); reg.h = mmu.read8b(i + 1); reg.m = 5;  };
		void LDmmHL () { auto i = mmu.read16b(reg.pc); reg.pc += 2; mmu.write16b(i, (reg.h << 8) + reg.l); reg.m = 5;  };
		void LDmmSP() { auto i = mmu.read16b(reg.pc); reg.pc += 2; mmu.write16b(i, reg.sp); reg.m = 5;  };

		void LDHLIA () { mmu.write8b((reg.h << 8) + reg.l, reg.a); reg.l = (reg.l + 1) & 255; if (!reg.l) reg.h = (reg.h + 1) & 255; reg.m = 2;  };
		void LDAHLI () { reg.a = mmu.read8b((reg.h << 8) + reg.l); reg.l = (reg.l + 1) & 255; if (!reg.l) reg.h = (reg.h + 1) & 255; reg.m = 2;  };

		void LDHLDA () { mmu.write8b((reg.h << 8) + reg.l, reg.a); reg.l = (reg.l - 1) & 255; if (reg.l == 255) reg.h = (reg.h - 1) & 255; reg.m = 2;  };
		void LDAHLD () { reg.a = mmu.read8b((reg.h << 8) + reg.l); reg.l = (reg.l - 1) & 255; if (reg.l == 255) reg.h = (reg.h - 1) & 255; reg.m = 2;  };

		void LDAIOn () { reg.a = mmu.read8b(0xFF00 + mmu.read8b(reg.pc)); reg.pc++; reg.m = 3;  };
		void LDIOnA () { mmu.write8b(0xFF00 + mmu.read8b(reg.pc), reg.a); reg.pc++; reg.m = 3;  };
		void LDAIOC () { reg.a = mmu.read8b(0xFF00 + reg.c); reg.m = 2;  };
		void LDIOCA () { mmu.write8b(0xFF00 + reg.c, reg.a); reg.m = 2;  };

		void LDHLSPn () { uint16_t i = mmu.read8b(reg.pc); if (i>127) i = -((~i + 1) & 255); reg.pc++; i += reg.sp; reg.h = (i >> 8) & 255; reg.l = i & 255; reg.m = 3;  };

		void SWAPr_b () { auto tr = reg.b; reg.b = mmu.read8b((reg.h << 8) + reg.l); mmu.write8b((reg.h << 8) + reg.l, tr); reg.m = 4;  };
		void SWAPr_c () { auto tr = reg.c; reg.c = mmu.read8b((reg.h << 8) + reg.l); mmu.write8b((reg.h << 8) + reg.l, tr); reg.m = 4;  };
		void SWAPr_d () { auto tr = reg.d; reg.d = mmu.read8b((reg.h << 8) + reg.l); mmu.write8b((reg.h << 8) + reg.l, tr); reg.m = 4;  };
		void SWAPr_e () { auto tr = reg.e; reg.e = mmu.read8b((reg.h << 8) + reg.l); mmu.write8b((reg.h << 8) + reg.l, tr); reg.m = 4;  };
		void SWAPr_h () { auto tr = reg.h; reg.h = mmu.read8b((reg.h << 8) + reg.l); mmu.write8b((reg.h << 8) + reg.l, tr); reg.m = 4;  };
		void SWAPr_l () { auto tr = reg.l; reg.l = mmu.read8b((reg.h << 8) + reg.l); mmu.write8b((reg.h << 8) + reg.l, tr); reg.m = 4;  };
		void SWAPr_a () { auto tr = reg.a; reg.a = mmu.read8b((reg.h << 8) + reg.l); mmu.write8b((reg.h << 8) + reg.l, tr); reg.m = 4;  };

		/*--- Data processing ---*/
		void ADDr_b() { auto a = reg.a; reg.a += reg.b; reg.f = (reg.a>255) ? 0x10 : 0; reg.a &= 255; if (!reg.a) reg.f |= 0x80; if ((reg.a^reg.b^a) & 0x10) reg.f |= 0x20; reg.m = 1; };
		void ADDr_c () { auto a = reg.a; reg.a += reg.c; reg.f = (reg.a>255) ? 0x10 : 0; reg.a &= 255; if (!reg.a) reg.f |= 0x80; if ((reg.a^reg.c^a) & 0x10) reg.f |= 0x20; reg.m = 1; };
		void ADDr_d () { auto a = reg.a; reg.a += reg.d; reg.f = (reg.a>255) ? 0x10 : 0; reg.a &= 255; if (!reg.a) reg.f |= 0x80; if ((reg.a^reg.d^a) & 0x10) reg.f |= 0x20; reg.m = 1; };
		void ADDr_e () { auto a = reg.a; reg.a += reg.e; reg.f = (reg.a>255) ? 0x10 : 0; reg.a &= 255; if (!reg.a) reg.f |= 0x80; if ((reg.a^reg.e^a) & 0x10) reg.f |= 0x20; reg.m = 1; };
		void ADDr_h () { auto a = reg.a; reg.a += reg.h; reg.f = (reg.a>255) ? 0x10 : 0; reg.a &= 255; if (!reg.a) reg.f |= 0x80; if ((reg.a^reg.h^a) & 0x10) reg.f |= 0x20; reg.m = 1; };
		void ADDr_l () { auto a = reg.a; reg.a += reg.l; reg.f = (reg.a>255) ? 0x10 : 0; reg.a &= 255; if (!reg.a) reg.f |= 0x80; if ((reg.a^reg.l^a) & 0x10) reg.f |= 0x20; reg.m = 1; };
		void ADDr_a () { auto a = reg.a; reg.a += reg.a; reg.f = (reg.a>255) ? 0x10 : 0; reg.a &= 255; if (!reg.a) reg.f |= 0x80; if ((reg.a^reg.a^a) & 0x10) reg.f |= 0x20; reg.m = 1; };
		void ADDHL () { auto a = reg.a; auto m = mmu.read8b((reg.h << 8) + reg.l); reg.a += m; reg.f = (reg.a>255) ? 0x10 : 0; reg.a &= 255; if (!reg.a) reg.f |= 0x80; if ((reg.a^a^m) & 0x10) reg.f |= 0x20; reg.m = 2; };
		void ADDn () { auto a = reg.a; auto m = mmu.read8b(reg.pc); reg.a += m; reg.pc++; reg.f = (reg.a>255) ? 0x10 : 0; reg.a &= 255; if (!reg.a) reg.f |= 0x80; if ((reg.a^a^m) & 0x10) reg.f |= 0x20; reg.m = 2; };
		void ADDHLBC () { auto hl = (reg.h << 8) + reg.l; hl += (reg.b << 8) + reg.c; if (hl>65535) reg.f |= 0x10; else reg.f &= 0xEF; reg.h = (hl >> 8) & 255; reg.l = hl & 255; reg.m = 3; };
		void ADDHLDE () { auto hl = (reg.h << 8) + reg.l; hl += (reg.d << 8) + reg.e; if (hl>65535) reg.f |= 0x10; else reg.f &= 0xEF; reg.h = (hl >> 8) & 255; reg.l = hl & 255; reg.m = 3; };
		void ADDHLHL () { auto hl = (reg.h << 8) + reg.l; hl += (reg.h << 8) + reg.l; if (hl>65535) reg.f |= 0x10; else reg.f &= 0xEF; reg.h = (hl >> 8) & 255; reg.l = hl & 255; reg.m = 3; };
		void ADDHLSP () { auto hl = (reg.h << 8) + reg.l; hl += reg.sp; if (hl>65535) reg.f |= 0x10; else reg.f &= 0xEF; reg.h = (hl >> 8) & 255; reg.l = hl & 255; reg.m = 3; };
		void ADDSPn () { auto i = mmu.read8b(reg.pc); if (i>127) i = -((~i + 1) & 255); reg.pc++; reg.sp += i; reg.m = 4; };

		void ADCr_b () { reg.a += reg.b; reg.a += (reg.f & 0x10) ? 1 : 0; fz(reg.a); if (reg.a>255) reg.f |= 0x10; reg.a &= 255; reg.m = 1;  };
		void ADCr_c () { reg.a += reg.c; reg.a += (reg.f & 0x10) ? 1 : 0; fz(reg.a); if (reg.a>255) reg.f |= 0x10; reg.a &= 255; reg.m = 1;  };
		void ADCr_d () { reg.a += reg.d; reg.a += (reg.f & 0x10) ? 1 : 0; fz(reg.a); if (reg.a>255) reg.f |= 0x10; reg.a &= 255; reg.m = 1;  };
		void ADCr_e () { reg.a += reg.e; reg.a += (reg.f & 0x10) ? 1 : 0; fz(reg.a); if (reg.a>255) reg.f |= 0x10; reg.a &= 255; reg.m = 1;  };
		void ADCr_h () { reg.a += reg.h; reg.a += (reg.f & 0x10) ? 1 : 0; fz(reg.a); if (reg.a>255) reg.f |= 0x10; reg.a &= 255; reg.m = 1;  };
		void ADCr_l () { reg.a += reg.l; reg.a += (reg.f & 0x10) ? 1 : 0; fz(reg.a); if (reg.a>255) reg.f |= 0x10; reg.a &= 255; reg.m = 1;  };
		void ADCr_a () { reg.a += reg.a; reg.a += (reg.f & 0x10) ? 1 : 0; fz(reg.a); if (reg.a>255) reg.f |= 0x10; reg.a &= 255; reg.m = 1;  };
		void ADCHL () { reg.a += mmu.read8b((reg.h << 8) + reg.l); reg.a += (reg.f & 0x10) ? 1 : 0; fz(reg.a); if (reg.a>255) reg.f |= 0x10; reg.a &= 255; reg.m = 2;  };
		void ADCn () { reg.a += mmu.read8b(reg.pc); reg.pc++; reg.a += (reg.f & 0x10) ? 1 : 0; fz(reg.a); if (reg.a>255) reg.f |= 0x10; reg.a &= 255; reg.m = 2;  };

		void SUBr_b () { reg.a -= reg.b; fz(reg.a, 1); if (reg.a<0) reg.f |= 0x10; reg.a &= 255; reg.m = 1;  };
		void SUBr_c () { reg.a -= reg.c; fz(reg.a, 1); if (reg.a<0) reg.f |= 0x10; reg.a &= 255; reg.m = 1;  };
		void SUBr_d () { reg.a -= reg.d; fz(reg.a, 1); if (reg.a<0) reg.f |= 0x10; reg.a &= 255; reg.m = 1;  };
		void SUBr_e () { reg.a -= reg.e; fz(reg.a, 1); if (reg.a<0) reg.f |= 0x10; reg.a &= 255; reg.m = 1;  };
		void SUBr_h () { reg.a -= reg.h; fz(reg.a, 1); if (reg.a<0) reg.f |= 0x10; reg.a &= 255; reg.m = 1;  };
		void SUBr_l () { reg.a -= reg.l; fz(reg.a, 1); if (reg.a<0) reg.f |= 0x10; reg.a &= 255; reg.m = 1;  };
		void SUBr_a () { reg.a -= reg.a; fz(reg.a, 1); if (reg.a<0) reg.f |= 0x10; reg.a &= 255; reg.m = 1;  };
		void SUBHL () { reg.a -= mmu.read8b((reg.h << 8) + reg.l); fz(reg.a, 1); if (reg.a<0) reg.f |= 0x10; reg.a &= 255; reg.m = 2;  };
		void SUBn () { reg.a -= mmu.read8b(reg.pc); reg.pc++; fz(reg.a, 1); if (reg.a<0) reg.f |= 0x10; reg.a &= 255; reg.m = 2;  };

		void SBCr_b () { reg.a -= reg.b; reg.a -= (reg.f & 0x10) ? 1 : 0; fz(reg.a, 1); if (reg.a<0) reg.f |= 0x10; reg.a &= 255; reg.m = 1;  };
		void SBCr_c () { reg.a -= reg.c; reg.a -= (reg.f & 0x10) ? 1 : 0; fz(reg.a, 1); if (reg.a<0) reg.f |= 0x10; reg.a &= 255; reg.m = 1;  };
		void SBCr_d () { reg.a -= reg.d; reg.a -= (reg.f & 0x10) ? 1 : 0; fz(reg.a, 1); if (reg.a<0) reg.f |= 0x10; reg.a &= 255; reg.m = 1;  };
		void SBCr_e () { reg.a -= reg.e; reg.a -= (reg.f & 0x10) ? 1 : 0; fz(reg.a, 1); if (reg.a<0) reg.f |= 0x10; reg.a &= 255; reg.m = 1;  };
		void SBCr_h () { reg.a -= reg.h; reg.a -= (reg.f & 0x10) ? 1 : 0; fz(reg.a, 1); if (reg.a<0) reg.f |= 0x10; reg.a &= 255; reg.m = 1;  };
		void SBCr_l () { reg.a -= reg.l; reg.a -= (reg.f & 0x10) ? 1 : 0; fz(reg.a, 1); if (reg.a<0) reg.f |= 0x10; reg.a &= 255; reg.m = 1;  };
		void SBCr_a () { reg.a -= reg.a; reg.a -= (reg.f & 0x10) ? 1 : 0; fz(reg.a, 1); if (reg.a<0) reg.f |= 0x10; reg.a &= 255; reg.m = 1;  };
		void SBCHL () { reg.a -= mmu.read8b((reg.h << 8) + reg.l); reg.a -= (reg.f & 0x10) ? 1 : 0; fz(reg.a, 1); if (reg.a<0) reg.f |= 0x10; reg.a &= 255; reg.m = 2;  };
		void SBCn () { reg.a -= mmu.read8b(reg.pc); reg.pc++; reg.a -= (reg.f & 0x10) ? 1 : 0; fz(reg.a, 1); if (reg.a<0) reg.f |= 0x10; reg.a &= 255; reg.m = 2;  };

		void CPr_b () { auto i = reg.a; i -= reg.b; fz(i, 1); if (i<0) reg.f |= 0x10; i &= 255; reg.m = 1;  };
		void CPr_c () { auto i = reg.a; i -= reg.c; fz(i, 1); if (i<0) reg.f |= 0x10; i &= 255; reg.m = 1;  };
		void CPr_d () { auto i = reg.a; i -= reg.d; fz(i, 1); if (i<0) reg.f |= 0x10; i &= 255; reg.m = 1;  };
		void CPr_e () { auto i = reg.a; i -= reg.e; fz(i, 1); if (i<0) reg.f |= 0x10; i &= 255; reg.m = 1;  };
		void CPr_h () { auto i = reg.a; i -= reg.h; fz(i, 1); if (i<0) reg.f |= 0x10; i &= 255; reg.m = 1;  };
		void CPr_l () { auto i = reg.a; i -= reg.l; fz(i, 1); if (i<0) reg.f |= 0x10; i &= 255; reg.m = 1;  };
		void CPr_a () { auto i = reg.a; i -= reg.a; fz(i, 1); if (i<0) reg.f |= 0x10; i &= 255; reg.m = 1;  };
		void CPHL () { auto i = reg.a; i -= mmu.read8b((reg.h << 8) + reg.l); fz(i, 1); if (i<0) reg.f |= 0x10; i &= 255; reg.m = 2;  };
		void CPn () { auto i = reg.a; i -= mmu.read8b(reg.pc); reg.pc++; fz(i, 1); if (i<0) reg.f |= 0x10; i &= 255; reg.m = 2;  };

		void DAA () { auto a = reg.a; if ((reg.f & 0x20) || ((reg.a & 15) > 9)) reg.a += 6; reg.f &= 0xEF; if ((reg.f & 0x20) || (a > 0x99)) { reg.a += 0x60; reg.f |= 0x10; } reg.m = 1; };

		void ANDr_b () { reg.a &= reg.b; reg.a &= 255; fz(reg.a); reg.m = 1;  };
		void ANDr_c () { reg.a &= reg.c; reg.a &= 255; fz(reg.a); reg.m = 1;  };
		void ANDr_d () { reg.a &= reg.d; reg.a &= 255; fz(reg.a); reg.m = 1;  };
		void ANDr_e () { reg.a &= reg.e; reg.a &= 255; fz(reg.a); reg.m = 1;  };
		void ANDr_h () { reg.a &= reg.h; reg.a &= 255; fz(reg.a); reg.m = 1;  };
		void ANDr_l () { reg.a &= reg.l; reg.a &= 255; fz(reg.a); reg.m = 1;  };
		void ANDr_a () { reg.a &= reg.a; reg.a &= 255; fz(reg.a); reg.m = 1;  };
		void ANDHL () { reg.a &= mmu.read8b((reg.h << 8) + reg.l); reg.a &= 255; fz(reg.a); reg.m = 2;  };
		void ANDn () { reg.a &= mmu.read8b(reg.pc); reg.pc++; reg.a &= 255; fz(reg.a); reg.m = 2;  };

		void ORr_b () { reg.a |= reg.b; reg.a &= 255; fz(reg.a); reg.m = 1;  };
		void ORr_c () { reg.a |= reg.c; reg.a &= 255; fz(reg.a); reg.m = 1;  };
		void ORr_d () { reg.a |= reg.d; reg.a &= 255; fz(reg.a); reg.m = 1;  };
		void ORr_e () { reg.a |= reg.e; reg.a &= 255; fz(reg.a); reg.m = 1;  };
		void ORr_h () { reg.a |= reg.h; reg.a &= 255; fz(reg.a); reg.m = 1;  };
		void ORr_l () { reg.a |= reg.l; reg.a &= 255; fz(reg.a); reg.m = 1;  };
		void ORr_a () { reg.a |= reg.a; reg.a &= 255; fz(reg.a); reg.m = 1;  };
		void ORHL () { reg.a |= mmu.read8b((reg.h << 8) + reg.l); reg.a &= 255; fz(reg.a); reg.m = 2;  };
		void ORn () { reg.a |= mmu.read8b(reg.pc); reg.pc++; reg.a &= 255; fz(reg.a); reg.m = 2;  };

		void XORr_b () { reg.a ^= reg.b; reg.a &= 255; fz(reg.a); reg.m = 1;  };
		void XORr_c () { reg.a ^= reg.c; reg.a &= 255; fz(reg.a); reg.m = 1;  };
		void XORr_d () { reg.a ^= reg.d; reg.a &= 255; fz(reg.a); reg.m = 1;  };
		void XORr_e () { reg.a ^= reg.e; reg.a &= 255; fz(reg.a); reg.m = 1;  };
		void XORr_h () { reg.a ^= reg.h; reg.a &= 255; fz(reg.a); reg.m = 1;  };
		void XORr_l () { reg.a ^= reg.l; reg.a &= 255; fz(reg.a); reg.m = 1;  };
		void XORr_a () { reg.a ^= reg.a; reg.a &= 255; fz(reg.a); reg.m = 1;  };
		void XORHL () { reg.a ^= mmu.read8b((reg.h << 8) + reg.l); reg.a &= 255; fz(reg.a); reg.m = 2;  };
		void XORn () { reg.a ^= mmu.read8b(reg.pc); reg.pc++; reg.a &= 255; fz(reg.a); reg.m = 2;  };

		void INCr_b () { reg.b++; reg.b &= 255; fz(reg.b); reg.m = 1;  };
		void INCr_c () { reg.c++; reg.c &= 255; fz(reg.c); reg.m = 1;  };
		void INCr_d () { reg.d++; reg.d &= 255; fz(reg.d); reg.m = 1;  };
		void INCr_e () { reg.e++; reg.e &= 255; fz(reg.e); reg.m = 1;  };
		void INCr_h () { reg.h++; reg.h &= 255; fz(reg.h); reg.m = 1;  };
		void INCr_l () { reg.l++; reg.l &= 255; fz(reg.l); reg.m = 1;  };
		void INCr_a () { reg.a++; reg.a &= 255; fz(reg.a); reg.m = 1;  };
		void INCHLm () { auto i = mmu.read8b((reg.h << 8) + reg.l) + 1; i &= 255; mmu.write8b((reg.h << 8) + reg.l, i); fz(i); reg.m = 3;  };

		void DECr_b () { reg.b--; reg.b &= 255; fz(reg.b); reg.m = 1;  };
		void DECr_c () { reg.c--; reg.c &= 255; fz(reg.c); reg.m = 1;  };
		void DECr_d () { reg.d--; reg.d &= 255; fz(reg.d); reg.m = 1;  };
		void DECr_e () { reg.e--; reg.e &= 255; fz(reg.e); reg.m = 1;  };
		void DECr_h () { reg.h--; reg.h &= 255; fz(reg.h); reg.m = 1;  };
		void DECr_l () { reg.l--; reg.l &= 255; fz(reg.l); reg.m = 1;  };
		void DECr_a () { reg.a--; reg.a &= 255; fz(reg.a); reg.m = 1;  };
		void DECHLm () { auto i = mmu.read8b((reg.h << 8) + reg.l) - 1; i &= 255; mmu.write8b((reg.h << 8) + reg.l, i); fz(i); reg.m = 3;  };

		void INCBC () { reg.c = (reg.c + 1) & 255; if (!reg.c) reg.b = (reg.b + 1) & 255; reg.m = 1;  };
		void INCDE () { reg.e = (reg.e + 1) & 255; if (!reg.e) reg.d = (reg.d + 1) & 255; reg.m = 1;  };
		void INCHL () { reg.l = (reg.l + 1) & 255; if (!reg.l) reg.h = (reg.h + 1) & 255; reg.m = 1;  };
		void INCSP () { reg.sp = (reg.sp + 1) & 65535; reg.m = 1;  };

		void DECBC () { reg.c = (reg.c - 1) & 255; if (reg.c == 255) reg.b = (reg.b - 1) & 255; reg.m = 1;  };
		void DECDE () { reg.e = (reg.e - 1) & 255; if (reg.e == 255) reg.d = (reg.d - 1) & 255; reg.m = 1;  };
		void DECHL () { reg.l = (reg.l - 1) & 255; if (reg.l == 255) reg.h = (reg.h - 1) & 255; reg.m = 1;  };
		void DECSP () { reg.sp = (reg.sp - 1) & 65535; reg.m = 1;  };

		/*--- Bit manipulation ---*/
		void BIT0b() { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.b & 0x01) ? 0 : 0x80; reg.m = 2; };
		void BIT0c () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.c & 0x01) ? 0 : 0x80; reg.m = 2; };
		void BIT0d () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.d & 0x01) ? 0 : 0x80; reg.m = 2; };
		void BIT0e () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.e & 0x01) ? 0 : 0x80; reg.m = 2; };
		void BIT0h () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.h & 0x01) ? 0 : 0x80; reg.m = 2; };
		void BIT0l () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.l & 0x01) ? 0 : 0x80; reg.m = 2; };
		void BIT0a () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.a & 0x01) ? 0 : 0x80; reg.m = 2; };
		void BIT0m () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (mmu.read8b((reg.h << 8) + reg.l) & 0x01) ? 0 : 0x80; reg.m = 3; };

		void RES0b () { reg.b &= 0xFE; reg.m = 2; };
		void RES0c () { reg.c &= 0xFE; reg.m = 2; };
		void RES0d () { reg.d &= 0xFE; reg.m = 2; };
		void RES0e () { reg.e &= 0xFE; reg.m = 2; };
		void RES0h () { reg.h &= 0xFE; reg.m = 2; };
		void RES0l () { reg.l &= 0xFE; reg.m = 2; };
		void RES0a () { reg.a &= 0xFE; reg.m = 2; };
		void RES0m () { auto i = mmu.read8b((reg.h << 8) + reg.l); i &= 0xFE; mmu.write8b((reg.h << 8) + reg.l, i); reg.m = 4; };

		void SET0b () { reg.b |= 0x01; reg.m = 2; };
		void SET0c () { reg.b |= 0x01; reg.m = 2; };
		void SET0d () { reg.b |= 0x01; reg.m = 2; };
		void SET0e () { reg.b |= 0x01; reg.m = 2; };
		void SET0h () { reg.b |= 0x01; reg.m = 2; };
		void SET0l () { reg.b |= 0x01; reg.m = 2; };
		void SET0a () { reg.b |= 0x01; reg.m = 2; };
		void SET0m () { auto i = mmu.read8b((reg.h << 8) + reg.l); i |= 0x01; mmu.write8b((reg.h << 8) + reg.l, i); reg.m = 4; };

		void BIT1b () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.b & 0x02) ? 0 : 0x80; reg.m = 2; };
		void BIT1c () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.c & 0x02) ? 0 : 0x80; reg.m = 2; };
		void BIT1d () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.d & 0x02) ? 0 : 0x80; reg.m = 2; };
		void BIT1e () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.e & 0x02) ? 0 : 0x80; reg.m = 2; };
		void BIT1h () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.h & 0x02) ? 0 : 0x80; reg.m = 2; };
		void BIT1l () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.l & 0x02) ? 0 : 0x80; reg.m = 2; };
		void BIT1a () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.a & 0x02) ? 0 : 0x80; reg.m = 2; };
		void BIT1m () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (mmu.read8b((reg.h << 8) + reg.l) & 0x02) ? 0 : 0x80; reg.m = 3; };

		void RES1b () { reg.b &= 0xFD; reg.m = 2; };
		void RES1c () { reg.c &= 0xFD; reg.m = 2; };
		void RES1d () { reg.d &= 0xFD; reg.m = 2; };
		void RES1e () { reg.e &= 0xFD; reg.m = 2; };
		void RES1h () { reg.h &= 0xFD; reg.m = 2; };
		void RES1l () { reg.l &= 0xFD; reg.m = 2; };
		void RES1a () { reg.a &= 0xFD; reg.m = 2; };
		void RES1m () { auto i = mmu.read8b((reg.h << 8) + reg.l); i &= 0xFD; mmu.write8b((reg.h << 8) + reg.l, i); reg.m = 4; };

		void SET1b () { reg.b |= 0x02; reg.m = 2; };
		void SET1c () { reg.b |= 0x02; reg.m = 2; };
		void SET1d () { reg.b |= 0x02; reg.m = 2; };
		void SET1e () { reg.b |= 0x02; reg.m = 2; };
		void SET1h () { reg.b |= 0x02; reg.m = 2; };
		void SET1l () { reg.b |= 0x02; reg.m = 2; };
		void SET1a () { reg.b |= 0x02; reg.m = 2; };
		void SET1m () { auto i = mmu.read8b((reg.h << 8) + reg.l); i |= 0x02; mmu.write8b((reg.h << 8) + reg.l, i); reg.m = 4; };

		void BIT2b () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.b & 0x04) ? 0 : 0x80; reg.m = 2; };
		void BIT2c() { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.c & 0x04) ? 0 : 0x80; reg.m = 2; };
		void BIT2d() { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.d & 0x04) ? 0 : 0x80; reg.m = 2; };
		void BIT2e () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.e & 0x04) ? 0 : 0x80; reg.m = 2; };
		void BIT2h () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.h & 0x04) ? 0 : 0x80; reg.m = 2; };
		void BIT2l () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.l & 0x04) ? 0 : 0x80; reg.m = 2; };
		void BIT2a () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.a & 0x04) ? 0 : 0x80; reg.m = 2; };
		void BIT2m () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (mmu.read8b((reg.h << 8) + reg.l) & 0x04) ? 0 : 0x80; reg.m = 3; };

		void RES2b () { reg.b &= 0xFB; reg.m = 2; };
		void RES2c () { reg.c &= 0xFB; reg.m = 2; };
		void RES2d () { reg.d &= 0xFB; reg.m = 2; };
		void RES2e () { reg.e &= 0xFB; reg.m = 2; };
		void RES2h () { reg.h &= 0xFB; reg.m = 2; };
		void RES2l () { reg.l &= 0xFB; reg.m = 2; };
		void RES2a () { reg.a &= 0xFB; reg.m = 2; };
		void RES2m () { auto i = mmu.read8b((reg.h << 8) + reg.l); i &= 0xFB; mmu.write8b((reg.h << 8) + reg.l, i); reg.m = 4; };

		void SET2b () { reg.b |= 0x04; reg.m = 2; };
		void SET2c () { reg.b |= 0x04; reg.m = 2; };
		void SET2d () { reg.b |= 0x04; reg.m = 2; };
		void SET2e () { reg.b |= 0x04; reg.m = 2; };
		void SET2h () { reg.b |= 0x04; reg.m = 2; };
		void SET2l () { reg.b |= 0x04; reg.m = 2; };
		void SET2a () { reg.b |= 0x04; reg.m = 2; };
		void SET2m () { auto i = mmu.read8b((reg.h << 8) + reg.l); i |= 0x04; mmu.write8b((reg.h << 8) + reg.l, i); reg.m = 4; };

		void BIT3b () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.b & 0x08) ? 0 : 0x80; reg.m = 2; };
		void BIT3c () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.c & 0x08) ? 0 : 0x80; reg.m = 2; };
		void BIT3d () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.d & 0x08) ? 0 : 0x80; reg.m = 2; };
		void BIT3e () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.e & 0x08) ? 0 : 0x80; reg.m = 2; };
		void BIT3h () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.h & 0x08) ? 0 : 0x80; reg.m = 2; };
		void BIT3l () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.l & 0x08) ? 0 : 0x80; reg.m = 2; };
		void BIT3a () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.a & 0x08) ? 0 : 0x80; reg.m = 2; };
		void BIT3m () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (mmu.read8b((reg.h << 8) + reg.l) & 0x08) ? 0 : 0x80; reg.m = 3; };

		void RES3b () { reg.b &= 0xF7; reg.m = 2; };
		void RES3c () { reg.c &= 0xF7; reg.m = 2; };
		void RES3d () { reg.d &= 0xF7; reg.m = 2; };
		void RES3e () { reg.e &= 0xF7; reg.m = 2; };
		void RES3h () { reg.h &= 0xF7; reg.m = 2; };
		void RES3l () { reg.l &= 0xF7; reg.m = 2; };
		void RES3a () { reg.a &= 0xF7; reg.m = 2; };
		void RES3m () { auto i = mmu.read8b((reg.h << 8) + reg.l); i &= 0xF7; mmu.write8b((reg.h << 8) + reg.l, i); reg.m = 4; };

		void SET3b() { reg.b |= 0x08; reg.m = 2; };
		void SET3c () { reg.b |= 0x08; reg.m = 2; };
		void SET3d () { reg.b |= 0x08; reg.m = 2; };
		void SET3e () { reg.b |= 0x08; reg.m = 2; };
		void SET3h () { reg.b |= 0x08; reg.m = 2; };
		void SET3l () { reg.b |= 0x08; reg.m = 2; };
		void SET3a () { reg.b |= 0x08; reg.m = 2; };
		void SET3m () { auto i = mmu.read8b((reg.h << 8) + reg.l); i |= 0x08; mmu.write8b((reg.h << 8) + reg.l, i); reg.m = 4; };

		void BIT4b () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.b & 0x10) ? 0 : 0x80; reg.m = 2; };
		void BIT4c () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.c & 0x10) ? 0 : 0x80; reg.m = 2; };
		void BIT4d () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.d & 0x10) ? 0 : 0x80; reg.m = 2; };
		void BIT4e () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.e & 0x10) ? 0 : 0x80; reg.m = 2; };
		void BIT4h () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.h & 0x10) ? 0 : 0x80; reg.m = 2; };
		void BIT4l () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.l & 0x10) ? 0 : 0x80; reg.m = 2; };
		void BIT4a () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.a & 0x10) ? 0 : 0x80; reg.m = 2; };
		void BIT4m () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (mmu.read8b((reg.h << 8) + reg.l) & 0x10) ? 0 : 0x80; reg.m = 3; };

		void RES4b () { reg.b &= 0xEF; reg.m = 2; };
		void RES4c () { reg.c &= 0xEF; reg.m = 2; };
		void RES4d () { reg.d &= 0xEF; reg.m = 2; };
		void RES4e () { reg.e &= 0xEF; reg.m = 2; };
		void RES4h () { reg.h &= 0xEF; reg.m = 2; };
		void RES4l () { reg.l &= 0xEF; reg.m = 2; };
		void RES4a () { reg.a &= 0xEF; reg.m = 2; };
		void RES4m () { auto i = mmu.read8b((reg.h << 8) + reg.l); i &= 0xEF; mmu.write8b((reg.h << 8) + reg.l, i); reg.m = 4; };

		void SET4b () { reg.b |= 0x10; reg.m = 2; };
		void SET4c () { reg.b |= 0x10; reg.m = 2; };
		void SET4d () { reg.b |= 0x10; reg.m = 2; };
		void SET4e () { reg.b |= 0x10; reg.m = 2; };
		void SET4h () { reg.b |= 0x10; reg.m = 2; };
		void SET4l () { reg.b |= 0x10; reg.m = 2; };
		void SET4a () { reg.b |= 0x10; reg.m = 2; };
		void SET4m () { auto i = mmu.read8b((reg.h << 8) + reg.l); i |= 0x10; mmu.write8b((reg.h << 8) + reg.l, i); reg.m = 4; };

		void BIT5b () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.b & 0x20) ? 0 : 0x80; reg.m = 2; };
		void BIT5c () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.c & 0x20) ? 0 : 0x80; reg.m = 2; };
		void BIT5d () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.d & 0x20) ? 0 : 0x80; reg.m = 2; };
		void BIT5e () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.e & 0x20) ? 0 : 0x80; reg.m = 2; };
		void BIT5h () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.h & 0x20) ? 0 : 0x80; reg.m = 2; };
		void BIT5l () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.l & 0x20) ? 0 : 0x80; reg.m = 2; };
		void BIT5a () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.a & 0x20) ? 0 : 0x80; reg.m = 2; };
		void BIT5m () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (mmu.read8b((reg.h << 8) + reg.l) & 0x20) ? 0 : 0x80; reg.m = 3; };

		void RES5b () { reg.b &= 0xDF; reg.m = 2; };
		void RES5c () { reg.c &= 0xDF; reg.m = 2; };
		void RES5d () { reg.d &= 0xDF; reg.m = 2; };
		void RES5e () { reg.e &= 0xDF; reg.m = 2; };
		void RES5h () { reg.h &= 0xDF; reg.m = 2; };
		void RES5l () { reg.l &= 0xDF; reg.m = 2; };
		void RES5a () { reg.a &= 0xDF; reg.m = 2; };
		void RES5m () { auto i = mmu.read8b((reg.h << 8) + reg.l); i &= 0xDF; mmu.write8b((reg.h << 8) + reg.l, i); reg.m = 4; };

		void SET5b () { reg.b |= 0x20; reg.m = 2; };
		void SET5c () { reg.b |= 0x20; reg.m = 2; };
		void SET5d () { reg.b |= 0x20; reg.m = 2; };
		void SET5e () { reg.b |= 0x20; reg.m = 2; };
		void SET5h () { reg.b |= 0x20; reg.m = 2; };
		void SET5l () { reg.b |= 0x20; reg.m = 2; };
		void SET5a () { reg.b |= 0x20; reg.m = 2; };
		void SET5m () { auto i = mmu.read8b((reg.h << 8) + reg.l); i |= 0x20; mmu.write8b((reg.h << 8) + reg.l, i); reg.m = 4; };

		void BIT6b () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.b & 0x40) ? 0 : 0x80; reg.m = 2; };
		void BIT6c () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.c & 0x40) ? 0 : 0x80; reg.m = 2; };
		void BIT6d () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.d & 0x40) ? 0 : 0x80; reg.m = 2; };
		void BIT6e () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.e & 0x40) ? 0 : 0x80; reg.m = 2; };
		void BIT6h () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.h & 0x40) ? 0 : 0x80; reg.m = 2; };
		void BIT6l () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.l & 0x40) ? 0 : 0x80; reg.m = 2; };
		void BIT6a () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.a & 0x40) ? 0 : 0x80; reg.m = 2; };
		void BIT6m () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (mmu.read8b((reg.h << 8) + reg.l) & 0x40) ? 0 : 0x80; reg.m = 3; };

		void RES6b () { reg.b &= 0xBF; reg.m = 2; };
		void RES6c () { reg.c &= 0xBF; reg.m = 2; };
		void RES6d () { reg.d &= 0xBF; reg.m = 2; };
		void RES6e () { reg.e &= 0xBF; reg.m = 2; };
		void RES6h () { reg.h &= 0xBF; reg.m = 2; };
		void RES6l () { reg.l &= 0xBF; reg.m = 2; };
		void RES6a () { reg.a &= 0xBF; reg.m = 2; };
		void RES6m () { auto i = mmu.read8b((reg.h << 8) + reg.l); i &= 0xBF; mmu.write8b((reg.h << 8) + reg.l, i); reg.m = 4; };

		void SET6b () { reg.b |= 0x40; reg.m = 2; };
		void SET6c () { reg.b |= 0x40; reg.m = 2; };
		void SET6d () { reg.b |= 0x40; reg.m = 2; };
		void SET6e () { reg.b |= 0x40; reg.m = 2; };
		void SET6h () { reg.b |= 0x40; reg.m = 2; };
		void SET6l () { reg.b |= 0x40; reg.m = 2; };
		void SET6a () { reg.b |= 0x40; reg.m = 2; };
		void SET6m () { auto i = mmu.read8b((reg.h << 8) + reg.l); i |= 0x40; mmu.write8b((reg.h << 8) + reg.l, i); reg.m = 4; };

		void BIT7b () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.b & 0x80) ? 0 : 0x80; reg.m = 2; };
		void BIT7c () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.c & 0x80) ? 0 : 0x80; reg.m = 2; };
		void BIT7d () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.d & 0x80) ? 0 : 0x80; reg.m = 2; };
		void BIT7e () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.e & 0x80) ? 0 : 0x80; reg.m = 2; };
		void BIT7h () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.h & 0x80) ? 0 : 0x80; reg.m = 2; };
		void BIT7l () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.l & 0x80) ? 0 : 0x80; reg.m = 2; };
		void BIT7a () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (reg.a & 0x80) ? 0 : 0x80; reg.m = 2; };
		void BIT7m () { reg.f &= 0x1F; reg.f |= 0x20; reg.f = (mmu.read8b((reg.h << 8) + reg.l) & 0x80) ? 0 : 0x80; reg.m = 3; };

		void RES7b () { reg.b &= 0x7F; reg.m = 2; };
		void RES7c () { reg.c &= 0x7F; reg.m = 2; };
		void RES7d () { reg.d &= 0x7F; reg.m = 2; };
		void RES7e () { reg.e &= 0x7F; reg.m = 2; };
		void RES7h () { reg.h &= 0x7F; reg.m = 2; };
		void RES7l () { reg.l &= 0x7F; reg.m = 2; };
		void RES7a () { reg.a &= 0x7F; reg.m = 2; };
		void RES7m () { auto i = mmu.read8b((reg.h << 8) + reg.l); i &= 0x7F; mmu.write8b((reg.h << 8) + reg.l, i); reg.m = 4; };

		void SET7b () { reg.b |= 0x80; reg.m = 2; };
		void SET7c () { reg.b |= 0x80; reg.m = 2; };
		void SET7d () { reg.b |= 0x80; reg.m = 2; };
		void SET7e () { reg.b |= 0x80; reg.m = 2; };
		void SET7h () { reg.b |= 0x80; reg.m = 2; };
		void SET7l () { reg.b |= 0x80; reg.m = 2; };
		void SET7a () { reg.b |= 0x80; reg.m = 2; };
		void SET7m () { auto i = mmu.read8b((reg.h << 8) + reg.l); i |= 0x80; mmu.write8b((reg.h << 8) + reg.l, i); reg.m = 4; };

		void RLA () { auto ci = reg.f & 0x10 ? 1 : 0; auto co = reg.a & 0x80 ? 0x10 : 0; reg.a = (reg.a << 1) + ci; reg.a &= 255; reg.f = (reg.f & 0xEF) + co; reg.m = 1;  };
		void RLCA () { auto ci = reg.a & 0x80 ? 1 : 0; auto co = reg.a & 0x80 ? 0x10 : 0; reg.a = (reg.a << 1) + ci; reg.a &= 255; reg.f = (reg.f & 0xEF) + co; reg.m = 1;  };
		void RRA () { auto ci = reg.f & 0x10 ? 0x80 : 0; auto co = reg.a & 1 ? 0x10 : 0; reg.a = (reg.a >> 1) + ci; reg.a &= 255; reg.f = (reg.f & 0xEF) + co; reg.m = 1;  };
		void RRCA () { auto ci = reg.a & 1 ? 0x80 : 0; auto co = reg.a & 1 ? 0x10 : 0; reg.a = (reg.a >> 1) + ci; reg.a &= 255; reg.f = (reg.f & 0xEF) + co; reg.m = 1;  };

		void RLr_b () { auto ci = reg.f & 0x10 ? 1 : 0; auto co = reg.b & 0x80 ? 0x10 : 0; reg.b = (reg.b << 1) + ci; reg.b &= 255; fz(reg.b); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RLr_c () { auto ci = reg.f & 0x10 ? 1 : 0; auto co = reg.c & 0x80 ? 0x10 : 0; reg.c = (reg.c << 1) + ci; reg.c &= 255; fz(reg.c); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RLr_d () { auto ci = reg.f & 0x10 ? 1 : 0; auto co = reg.d & 0x80 ? 0x10 : 0; reg.d = (reg.d << 1) + ci; reg.d &= 255; fz(reg.d); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RLr_e () { auto ci = reg.f & 0x10 ? 1 : 0; auto co = reg.e & 0x80 ? 0x10 : 0; reg.e = (reg.e << 1) + ci; reg.e &= 255; fz(reg.e); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RLr_h () { auto ci = reg.f & 0x10 ? 1 : 0; auto co = reg.h & 0x80 ? 0x10 : 0; reg.h = (reg.h << 1) + ci; reg.h &= 255; fz(reg.h); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RLr_l () { auto ci = reg.f & 0x10 ? 1 : 0; auto co = reg.l & 0x80 ? 0x10 : 0; reg.l = (reg.l << 1) + ci; reg.l &= 255; fz(reg.l); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RLr_a () { auto ci = reg.f & 0x10 ? 1 : 0; auto co = reg.a & 0x80 ? 0x10 : 0; reg.a = (reg.a << 1) + ci; reg.a &= 255; fz(reg.a); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RLHL () { auto i = mmu.read8b((reg.h << 8) + reg.l); auto ci = reg.f & 0x10 ? 1 : 0; auto co = i & 0x80 ? 0x10 : 0; i = (i << 1) + ci; i &= 255; fz(i); mmu.write8b((reg.h << 8) + reg.l, i); reg.f = (reg.f & 0xEF) + co; reg.m = 4;  };

		void RLCr_b () { auto ci = reg.b & 0x80 ? 1 : 0; auto co = reg.b & 0x80 ? 0x10 : 0; reg.b = (reg.b << 1) + ci; reg.b &= 255; fz(reg.b); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RLCr_c () { auto ci = reg.c & 0x80 ? 1 : 0; auto co = reg.c & 0x80 ? 0x10 : 0; reg.c = (reg.c << 1) + ci; reg.c &= 255; fz(reg.c); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RLCr_d () { auto ci = reg.d & 0x80 ? 1 : 0; auto co = reg.d & 0x80 ? 0x10 : 0; reg.d = (reg.d << 1) + ci; reg.d &= 255; fz(reg.d); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RLCr_e () { auto ci = reg.e & 0x80 ? 1 : 0; auto co = reg.e & 0x80 ? 0x10 : 0; reg.e = (reg.e << 1) + ci; reg.e &= 255; fz(reg.e); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RLCr_h () { auto ci = reg.h & 0x80 ? 1 : 0; auto co = reg.h & 0x80 ? 0x10 : 0; reg.h = (reg.h << 1) + ci; reg.h &= 255; fz(reg.h); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RLCr_l () { auto ci = reg.l & 0x80 ? 1 : 0; auto co = reg.l & 0x80 ? 0x10 : 0; reg.l = (reg.l << 1) + ci; reg.l &= 255; fz(reg.l); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RLCr_a () { auto ci = reg.a & 0x80 ? 1 : 0; auto co = reg.a & 0x80 ? 0x10 : 0; reg.a = (reg.a << 1) + ci; reg.a &= 255; fz(reg.a); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RLCHL () { auto i = mmu.read8b((reg.h << 8) + reg.l); auto ci = i & 0x80 ? 1 : 0; auto co = i & 0x80 ? 0x10 : 0; i = (i << 1) + ci; i &= 255; fz(i); mmu.write8b((reg.h << 8) + reg.l, i); reg.f = (reg.f & 0xEF) + co; reg.m = 4;  };

		void RRr_b () { auto ci = reg.f & 0x10 ? 0x80 : 0; auto co = reg.b & 1 ? 0x10 : 0; reg.b = (reg.b >> 1) + ci; reg.b &= 255; fz(reg.b); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RRr_c () { auto ci = reg.f & 0x10 ? 0x80 : 0; auto co = reg.c & 1 ? 0x10 : 0; reg.c = (reg.c >> 1) + ci; reg.c &= 255; fz(reg.c); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RRr_d () { auto ci = reg.f & 0x10 ? 0x80 : 0; auto co = reg.d & 1 ? 0x10 : 0; reg.d = (reg.d >> 1) + ci; reg.d &= 255; fz(reg.d); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RRr_e () { auto ci = reg.f & 0x10 ? 0x80 : 0; auto co = reg.e & 1 ? 0x10 : 0; reg.e = (reg.e >> 1) + ci; reg.e &= 255; fz(reg.e); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RRr_h () { auto ci = reg.f & 0x10 ? 0x80 : 0; auto co = reg.h & 1 ? 0x10 : 0; reg.h = (reg.h >> 1) + ci; reg.h &= 255; fz(reg.h); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RRr_l () { auto ci = reg.f & 0x10 ? 0x80 : 0; auto co = reg.l & 1 ? 0x10 : 0; reg.l = (reg.l >> 1) + ci; reg.l &= 255; fz(reg.l); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RRr_a () { auto ci = reg.f & 0x10 ? 0x80 : 0; auto co = reg.a & 1 ? 0x10 : 0; reg.a = (reg.a >> 1) + ci; reg.a &= 255; fz(reg.a); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RRHL () { auto i = mmu.read8b((reg.h << 8) + reg.l); auto ci = reg.f & 0x10 ? 0x80 : 0; auto co = i & 1 ? 0x10 : 0; i = (i >> 1) + ci; i &= 255; mmu.write8b((reg.h << 8) + reg.l, i); fz(i); reg.f = (reg.f & 0xEF) + co; reg.m = 4;  };

		void RRCr_b () { auto ci = reg.b & 1 ? 0x80 : 0; auto co = reg.b & 1 ? 0x10 : 0; reg.b = (reg.b >> 1) + ci; reg.b &= 255; fz(reg.b); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RRCr_c () { auto ci = reg.c & 1 ? 0x80 : 0; auto co = reg.c & 1 ? 0x10 : 0; reg.c = (reg.c >> 1) + ci; reg.c &= 255; fz(reg.c); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RRCr_d () { auto ci = reg.d & 1 ? 0x80 : 0; auto co = reg.d & 1 ? 0x10 : 0; reg.d = (reg.d >> 1) + ci; reg.d &= 255; fz(reg.d); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RRCr_e () { auto ci = reg.e & 1 ? 0x80 : 0; auto co = reg.e & 1 ? 0x10 : 0; reg.e = (reg.e >> 1) + ci; reg.e &= 255; fz(reg.e); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RRCr_h () { auto ci = reg.h & 1 ? 0x80 : 0; auto co = reg.h & 1 ? 0x10 : 0; reg.h = (reg.h >> 1) + ci; reg.h &= 255; fz(reg.h); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RRCr_l () { auto ci = reg.l & 1 ? 0x80 : 0; auto co = reg.l & 1 ? 0x10 : 0; reg.l = (reg.l >> 1) + ci; reg.l &= 255; fz(reg.l); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RRCr_a () { auto ci = reg.a & 1 ? 0x80 : 0; auto co = reg.a & 1 ? 0x10 : 0; reg.a = (reg.a >> 1) + ci; reg.a &= 255; fz(reg.a); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void RRCHL () { auto i = mmu.read8b((reg.h << 8) + reg.l); auto ci = i & 1 ? 0x80 : 0; auto co = i & 1 ? 0x10 : 0; i = (i >> 1) + ci; i &= 255; mmu.write8b((reg.h << 8) + reg.l, i); fz(i); reg.f = (reg.f & 0xEF) + co; reg.m = 4;  };

		void SLAr_b () { auto co = reg.b & 0x80 ? 0x10 : 0; reg.b = (reg.b << 1) & 255; fz(reg.b); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void SLAr_c () { auto co = reg.c & 0x80 ? 0x10 : 0; reg.c = (reg.c << 1) & 255; fz(reg.c); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void SLAr_d () { auto co = reg.d & 0x80 ? 0x10 : 0; reg.d = (reg.d << 1) & 255; fz(reg.d); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void SLAr_e () { auto co = reg.e & 0x80 ? 0x10 : 0; reg.e = (reg.e << 1) & 255; fz(reg.e); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void SLAr_h () { auto co = reg.h & 0x80 ? 0x10 : 0; reg.h = (reg.h << 1) & 255; fz(reg.h); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void SLAr_l () { auto co = reg.l & 0x80 ? 0x10 : 0; reg.l = (reg.l << 1) & 255; fz(reg.l); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void SLAr_a () { auto co = reg.a & 0x80 ? 0x10 : 0; reg.a = (reg.a << 1) & 255; fz(reg.a); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };

		void SLLr_b () { auto co = reg.b & 0x80 ? 0x10 : 0; reg.b = (reg.b << 1) & 255 + 1; fz(reg.b); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void SLLr_c () { auto co = reg.c & 0x80 ? 0x10 : 0; reg.c = (reg.c << 1) & 255 + 1; fz(reg.c); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void SLLr_d () { auto co = reg.d & 0x80 ? 0x10 : 0; reg.d = (reg.d << 1) & 255 + 1; fz(reg.d); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void SLLr_e () { auto co = reg.e & 0x80 ? 0x10 : 0; reg.e = (reg.e << 1) & 255 + 1; fz(reg.e); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void SLLr_h () { auto co = reg.h & 0x80 ? 0x10 : 0; reg.h = (reg.h << 1) & 255 + 1; fz(reg.h); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void SLLr_l () { auto co = reg.l & 0x80 ? 0x10 : 0; reg.l = (reg.l << 1) & 255 + 1; fz(reg.l); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void SLLr_a () { auto co = reg.a & 0x80 ? 0x10 : 0; reg.a = (reg.a << 1) & 255 + 1; fz(reg.a); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };

		void SRAr_b () { auto ci = reg.b & 0x80; auto co = reg.b & 1 ? 0x10 : 0; reg.b = ((reg.b >> 1) + ci) & 255; fz(reg.b); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void SRAr_c () { auto ci = reg.c & 0x80; auto co = reg.c & 1 ? 0x10 : 0; reg.c = ((reg.c >> 1) + ci) & 255; fz(reg.c); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void SRAr_d () { auto ci = reg.d & 0x80; auto co = reg.d & 1 ? 0x10 : 0; reg.d = ((reg.d >> 1) + ci) & 255; fz(reg.d); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void SRAr_e () { auto ci = reg.e & 0x80; auto co = reg.e & 1 ? 0x10 : 0; reg.e = ((reg.e >> 1) + ci) & 255; fz(reg.e); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void SRAr_h () { auto ci = reg.h & 0x80; auto co = reg.h & 1 ? 0x10 : 0; reg.h = ((reg.h >> 1) + ci) & 255; fz(reg.h); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void SRAr_l () { auto ci = reg.l & 0x80; auto co = reg.l & 1 ? 0x10 : 0; reg.l = ((reg.l >> 1) + ci) & 255; fz(reg.l); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void SRAr_a () { auto ci = reg.a & 0x80; auto co = reg.a & 1 ? 0x10 : 0; reg.a = ((reg.a >> 1) + ci) & 255; fz(reg.a); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };

		void SRLr_b () { auto co = reg.b & 1 ? 0x10 : 0; reg.b = (reg.b >> 1) & 255; fz(reg.b); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void SRLr_c () { auto co = reg.c & 1 ? 0x10 : 0; reg.c = (reg.c >> 1) & 255; fz(reg.c); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void SRLr_d () { auto co = reg.d & 1 ? 0x10 : 0; reg.d = (reg.d >> 1) & 255; fz(reg.d); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void SRLr_e () { auto co = reg.e & 1 ? 0x10 : 0; reg.e = (reg.e >> 1) & 255; fz(reg.e); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void SRLr_h () { auto co = reg.h & 1 ? 0x10 : 0; reg.h = (reg.h >> 1) & 255; fz(reg.h); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void SRLr_l () { auto co = reg.l & 1 ? 0x10 : 0; reg.l = (reg.l >> 1) & 255; fz(reg.l); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };
		void SRLr_a () { auto co = reg.a & 1 ? 0x10 : 0; reg.a = (reg.a >> 1) & 255; fz(reg.a); reg.f = (reg.f & 0xEF) + co; reg.m = 2;  };

		void CPL () { reg.a = (~reg.a) & 255; fz(reg.a, 1); reg.m = 1;  };
		void NEG () { reg.a = 0 - reg.a; fz(reg.a, 1); if (reg.a<0) reg.f |= 0x10; reg.a &= 255; reg.m = 2;  };

		void CCF () { auto ci = reg.f & 0x10 ? 0 : 0x10; reg.f = (reg.f & 0xEF) + ci; reg.m = 1;  };
		void SCF () { reg.f |= 0x10; reg.m = 1;  };

		/*--- Stack ---*/
		void PUSHBC () { reg.sp--; mmu.write8b(reg.sp, reg.b); reg.sp--; mmu.write8b(reg.sp, reg.c); reg.m = 3;  };
		void PUSHDE () { reg.sp--; mmu.write8b(reg.sp, reg.d); reg.sp--; mmu.write8b(reg.sp, reg.e); reg.m = 3;  };
		void PUSHHL () { reg.sp--; mmu.write8b(reg.sp, reg.h); reg.sp--; mmu.write8b(reg.sp, reg.l); reg.m = 3;  };
		void PUSHAF () { reg.sp--; mmu.write8b(reg.sp, reg.a); reg.sp--; mmu.write8b(reg.sp, reg.f); reg.m = 3;  };

		void POPBC () { reg.c = mmu.read8b(reg.sp); reg.sp++; reg.b = mmu.read8b(reg.sp); reg.sp++; reg.m = 3;  };
		void POPDE () { reg.e = mmu.read8b(reg.sp); reg.sp++; reg.d = mmu.read8b(reg.sp); reg.sp++; reg.m = 3;  };
		void POPHL () { reg.l = mmu.read8b(reg.sp); reg.sp++; reg.h = mmu.read8b(reg.sp); reg.sp++; reg.m = 3;  };
		void POPAF () { reg.f = mmu.read8b(reg.sp); reg.sp++; reg.a = mmu.read8b(reg.sp); reg.sp++; reg.m = 3;  };

		/*--- Jump ---*/
		void JPnn () { reg.pc = mmu.read16b(reg.pc); reg.m = 3;  };
		void JPHL () { reg.pc = (reg.h << 8) + reg.l; reg.m = 1;  };
		void JPNZnn () { reg.m = 3;  if ((reg.f & 0x80) == 0x00) { reg.pc = mmu.read16b(reg.pc); reg.m++;  } else reg.pc += 2; };
		void JPZnn () { reg.m = 3;  if ((reg.f & 0x80) == 0x80) { reg.pc = mmu.read16b(reg.pc); reg.m++;  } else reg.pc += 2; };
		void JPNCnn () { reg.m = 3;  if ((reg.f & 0x10) == 0x00) { reg.pc = mmu.read16b(reg.pc); reg.m++;  } else reg.pc += 2; };
		void JPCnn () { reg.m = 3;  if ((reg.f & 0x10) == 0x10) { reg.pc = mmu.read16b(reg.pc); reg.m++;  } else reg.pc += 2; };

		void JRn () { auto i = mmu.read8b(reg.pc); if (i>127) i = -((~i + 1) & 255); reg.pc++; reg.m = 2;  reg.pc += i; reg.m++;  };
		void JRNZn () { auto i = mmu.read8b(reg.pc); if (i>127) i = -((~i + 1) & 255); reg.pc++; reg.m = 2;  if ((reg.f & 0x80) == 0x00) { reg.pc += i; reg.m++;  } };
		void JRZn () { auto i = mmu.read8b(reg.pc); if (i>127) i = -((~i + 1) & 255); reg.pc++; reg.m = 2;  if ((reg.f & 0x80) == 0x80) { reg.pc += i; reg.m++;  } };
		void JRNCn () { auto i = mmu.read8b(reg.pc); if (i>127) i = -((~i + 1) & 255); reg.pc++; reg.m = 2;  if ((reg.f & 0x10) == 0x00) { reg.pc += i; reg.m++;  } };
		void JRCn () { auto i = mmu.read8b(reg.pc); if (i>127) i = -((~i + 1) & 255); reg.pc++; reg.m = 2;  if ((reg.f & 0x10) == 0x10) { reg.pc += i; reg.m++;  } };

		void DJNZn () { auto i = mmu.read8b(reg.pc); if (i>127) i = -((~i + 1) & 255); reg.pc++; reg.m = 2;  reg.b--; if (reg.b) { reg.pc += i; reg.m++;  } };

		void CALLnn () { reg.sp -= 2; mmu.write16b(reg.sp, reg.pc + 2); reg.pc = mmu.read16b(reg.pc); reg.m = 5;  };
		void CALLNZnn () { reg.m = 3;  if ((reg.f & 0x80) == 0x00) { reg.sp -= 2; mmu.write16b(reg.sp, reg.pc + 2); reg.pc = mmu.read16b(reg.pc); reg.m += 2;  } else reg.pc += 2; };
		void CALLZnn () { reg.m = 3;  if ((reg.f & 0x80) == 0x80) { reg.sp -= 2; mmu.write16b(reg.sp, reg.pc + 2); reg.pc = mmu.read16b(reg.pc); reg.m += 2;  } else reg.pc += 2; };
		void CALLNCnn () { reg.m = 3;  if ((reg.f & 0x10) == 0x00) { reg.sp -= 2; mmu.write16b(reg.sp, reg.pc + 2); reg.pc = mmu.read16b(reg.pc); reg.m += 2;  } else reg.pc += 2; };
		void CALLCnn () { reg.m = 3;  if ((reg.f & 0x10) == 0x10) { reg.sp -= 2; mmu.write16b(reg.sp, reg.pc + 2); reg.pc = mmu.read16b(reg.pc); reg.m += 2;  } else reg.pc += 2; };

		void RET () { reg.pc = mmu.read16b(reg.sp); reg.sp += 2; reg.m = 3;  };
		void RETI () { reg.ime = 1; reg.pc = mmu.read16b(reg.sp); reg.sp += 2; reg.m = 3;  };
		void RETNZ () { reg.m = 1;  if ((reg.f & 0x80) == 0x00) { reg.pc = mmu.read16b(reg.sp); reg.sp += 2; reg.m += 2;  } };
		void RETZ () { reg.m = 1;  if ((reg.f & 0x80) == 0x80) { reg.pc = mmu.read16b(reg.sp); reg.sp += 2; reg.m += 2;  } };
		void RETNC () { reg.m = 1;  if ((reg.f & 0x10) == 0x00) { reg.pc = mmu.read16b(reg.sp); reg.sp += 2; reg.m += 2;  } };
		void RETC () { reg.m = 1;  if ((reg.f & 0x10) == 0x10) { reg.pc = mmu.read16b(reg.sp); reg.sp += 2; reg.m += 2;  } };

		void RST00 () { reg.sp -= 2; mmu.write16b(reg.sp, reg.pc); reg.pc = 0x00; reg.m = 3;  };
		void RST08 () { reg.sp -= 2; mmu.write16b(reg.sp, reg.pc); reg.pc = 0x08; reg.m = 3;  };
		void RST10 () { reg.sp -= 2; mmu.write16b(reg.sp, reg.pc); reg.pc = 0x10; reg.m = 3;  };
		void RST18 () { reg.sp -= 2; mmu.write16b(reg.sp, reg.pc); reg.pc = 0x18; reg.m = 3;  };
		void RST20 () { reg.sp -= 2; mmu.write16b(reg.sp, reg.pc); reg.pc = 0x20; reg.m = 3;  };
		void RST28 () { reg.sp -= 2; mmu.write16b(reg.sp, reg.pc); reg.pc = 0x28; reg.m = 3;  };
		void RST30 () { reg.sp -= 2; mmu.write16b(reg.sp, reg.pc); reg.pc = 0x30; reg.m = 3;  };
		void RST38 () { reg.sp -= 2; mmu.write16b(reg.sp, reg.pc); reg.pc = 0x38; reg.m = 3;  };
		void RST40 () { reg.sp -= 2; mmu.write16b(reg.sp, reg.pc); reg.pc = 0x40; reg.m = 3;  };
		void RST48 () { reg.sp -= 2; mmu.write16b(reg.sp, reg.pc); reg.pc = 0x48; reg.m = 3;  };
		void RST50 () { reg.sp -= 2; mmu.write16b(reg.sp, reg.pc); reg.pc = 0x50; reg.m = 3;  };
		void RST58 () { reg.sp -= 2; mmu.write16b(reg.sp, reg.pc); reg.pc = 0x58; reg.m = 3;  };
		void RST60 () { reg.sp -= 2; mmu.write16b(reg.sp, reg.pc); reg.pc = 0x60; reg.m = 3;  };

		void NOP () { reg.m = 1;  };
		void HALT () { reg.halt = true; reg.m = 1;  };

		void DI () { reg.ime = false; reg.m = 1;  };
		void EI () { reg.ime = true; reg.m = 1;  };

	};

	void	run();
	void	processInput(SDL_Event &ev);
	int		*getPixels();

	template <typename T, typename ... Args>
	void	addModule(typename Args &&... args)
	{
		_modules.push_back(std::make_unique<T>(std::forward<Args>(args)...));
	}
	
private:
	CPU										_z80;
	bool									_loop = true;
	std::vector<std::unique_ptr<Module>>	_modules;
};
