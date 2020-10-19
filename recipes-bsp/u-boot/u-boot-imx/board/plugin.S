/*
 * Copyright (c) 2017 iWave Systems Technologies Pvt. Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
 
/*
 * @file  plugin.S
 * 
 * @brief DDR settings for iwaves iMx6x SM SOMs 
 *
 * @ingroup DDR Setting
 */

#include <config.h>

/* DDR script */
.macro imx6dq_iwg15m_ddr_setting
	ldr r0, =IOMUXC_BASE_ADDR
	ldr r1, =0x000c0000
	str r1, [r0, #0x798]
	ldr r1, =0x00000000
	str r1, [r0, #0x758]

	ldr r1, =0x00000030
	str r1, [r0, #0x588]
	str r1, [r0, #0x594]
	str r1, [r0, #0x56c]
	str r1, [r0, #0x578]
	str r1, [r0, #0x74c]
	str r1, [r0, #0x57c]

	ldr r1, =0x00000000
	str r1, [r0, #0x58c]

	ldr r1, =0x00000030
	str r1, [r0, #0x59c]
	str r1, [r0, #0x5a0]
	str r1, [r0, #0x78c]

	ldr r1, =0x00020000
	str r1, [r0, #0x750]

	ldr r1, =0x00000030
	str r1, [r0, #0x5a8]
	str r1, [r0, #0x5b0]
	str r1, [r0, #0x524]
	str r1, [r0, #0x51c]
	str r1, [r0, #0x518]
	str r1, [r0, #0x50c]
	str r1, [r0, #0x5b8]
	str r1, [r0, #0x5c0]

	ldr r1, =0x00020000
	str r1, [r0, #0x774]

	ldr r1, =0x00000030
	str r1, [r0, #0x784]
	str r1, [r0, #0x788]
	str r1, [r0, #0x794]
	str r1, [r0, #0x79c]
	str r1, [r0, #0x7a0]
	str r1, [r0, #0x7a4]
	str r1, [r0, #0x7a8]
	str r1, [r0, #0x748]
	str r1, [r0, #0x5ac]
	str r1, [r0, #0x5b4]
	str r1, [r0, #0x528]
	str r1, [r0, #0x520]
	str r1, [r0, #0x514]
	str r1, [r0, #0x510]
	str r1, [r0, #0x5bc]
	str r1, [r0, #0x5c4]

	ldr r0, =MMDC_P0_BASE_ADDR
	ldr r2, =0x00008000
	str r2, [r0, #0x01c]
	ldr r2, =0xa1390003
	str r2, [r0, #0x800]

	ldr r2, =0x00250025
	str r2, [r0, #0x80c]
	ldr r2, =0x00270022
	str r2, [r0, #0x810]
	ldr r1, =MMDC_P1_BASE_ADDR
	ldr r2, =0x00100024
	str r2, [r1, #0x80c]
	ldr r2, =0x000E0024
	str r2, [r1, #0x810]

	ldr r2, =0x0330034C
	str r2, [r0, #0x83c]
	ldr r2, =0x033C0330
	str r2, [r0, #0x840]

	ldr r2, =0x03440350
	str r2, [r1, #0x83c]
	ldr r2, =0x03340300
	str r2, [r1, #0x840]

	ldr r2, =0x42383A3E
	str r2, [r0, #0x848]
	ldr r2, =0x40383844
	str r2, [r1, #0x848]

	ldr r2, =0x34363C36
	str r2, [r0, #0x850]
	ldr r2, =0x40304A3C
	str r2, [r1, #0x850]

	ldr r2, =0x33333333
	str r2, [r0, #0x81c]
	str r2, [r0, #0x820]
	str r2, [r0, #0x824]
	str r2, [r0, #0x828]
	str r2, [r1, #0x81c]
	str r2, [r1, #0x820]
	str r2, [r1, #0x824]
	str r2, [r1, #0x828]

	ldr r2, =0x00000800
	str r2, [r0, #0x8b8]
	str r2, [r1, #0x8b8]

	ldr r2, =0x00020036
	str r2, [r0, #0x004]
	ldr r2, =0x09444040
	str r2, [r0, #0x008]

	ldr r2, =0x54597955
	str r2, [r0, #0x00c]
	ldr r2, =0xFF328F64
	str r2, [r0, #0x010]

	ldr r2, =0x01FF00DB
	str r2, [r0, #0x014]
	ldr r2, =0x00011740
	str r2, [r0, #0x018]

	ldr r2, =0x00008000
	str r2, [r0, #0x01c]
	ldr r2, =0x000026d2
	str r2, [r0, #0x02c]
	ldr r2, =0x00591023
	str r2, [r0, #0x030]
	ldr r2, =0x00000027
	str r2, [r0, #0x040]

	ldr r2, =0x831A0000
	str r2, [r0, #0x000]

	ldr r2, =0x02088032
	str r2, [r0, #0x01c]
	ldr r2, =0x00008033
	str r2, [r0, #0x01c]
	ldr r2, =0x00048031
	str r2, [r0, #0x01c]
	ldr r2, =0x19408030
	str r2, [r0, #0x01c]
	ldr r2, =0x04008040
	str r2, [r0, #0x01c]

	ldr r2, =0x00007800
	str r2, [r0, #0x020]
	ldr r2, =0x00022227
	str r2, [r0, #0x818]
	str r2, [r1, #0x818]
	ldr r2, =0x00025576
	str r2, [r0, #0x004]
	ldr r2, =0x00011006
	str r2, [r0, #0x404]
	ldr r2, =0x00000000
	str r2, [r0, #0x01c]
.endm

.macro imx6dl_iwg15m_ddr_setting
	ldr r0, =IOMUXC_BASE_ADDR
	ldr r1, =0x000c0000
	str r1, [r0, #0x774]
	ldr r1, =0x00000000
	str r1, [r0, #0x754]

	ldr r1, =0x00000030
	str r1, [r0, #0x4ac]
	str r1, [r0, #0x4b0]
	str r1, [r0, #0x464]
	str r1, [r0, #0x490]
	str r1, [r0, #0x74c]
	str r1, [r0, #0x494]

	ldr r1, =0x00000000
	str r1, [r0, #0x4a0]

	ldr r1, =0x00000030
	str r1, [r0, #0x4b4]
	str r1, [r0, #0x4b8]
	str r1, [r0, #0x76c]

	ldr r1, =0x00020000
	str r1, [r0, #0x750]

	ldr r1, =0x00000030
	str r1, [r0, #0x4bc]
	str r1, [r0, #0x4c0]
	str r1, [r0, #0x4c4]
	str r1, [r0, #0x4c8]
	str r1, [r0, #0x4cc]
	str r1, [r0, #0x4d0]
	str r1, [r0, #0x4d4]
	str r1, [r0, #0x4d8]

	ldr r1, =0x00020000
	str r1, [r0, #0x760]

	ldr r1, =0x00000030
	str r1, [r0, #0x764]
	str r1, [r0, #0x770]
	str r1, [r0, #0x778]
	str r1, [r0, #0x77c]
	str r1, [r0, #0x780]
	str r1, [r0, #0x784]
	str r1, [r0, #0x78c]
	str r1, [r0, #0x748]
	str r1, [r0, #0x470]
	str r1, [r0, #0x474]
	str r1, [r0, #0x478]
	str r1, [r0, #0x47c]
	str r1, [r0, #0x480]
	str r1, [r0, #0x484]
	str r1, [r0, #0x488]
	str r1, [r0, #0x48c]

	ldr r0, =MMDC_P0_BASE_ADDR
	ldr r2, =0x00008000
	str r2, [r0, #0x01c]
	ldr r2, =0xa1390003
	str r2, [r0, #0x800]

	ldr r2, =0x004F0051
	str r2, [r0, #0x80c]
	ldr r2, =0x003F0044
	str r2, [r0, #0x810]
	ldr r1, =MMDC_P1_BASE_ADDR
	ldr r2, =0x0027002B
	str r2, [r1, #0x80c]
	ldr r2, =0x002D0045
	str r2, [r1, #0x810]

	ldr r2, =0x02500258
	str r2, [r0, #0x83c]
	ldr r2, =0x02400240
	str r2, [r0, #0x840]

	ldr r2, =0x02340240
	str r2, [r1, #0x83c]
	ldr r2, =0x02280230
	str r2, [r1, #0x840]

	ldr r2, =0x444A4E4A
	str r2, [r0, #0x848]
	ldr r2, =0x4C4C4E44
	str r2, [r1, #0x848]

	ldr r2, =0x34342A2E
	str r2, [r0, #0x850]
	ldr r2, =0x3434342C
	str r2, [r1, #0x850]

	ldr r2, =0x33333333
	str r2, [r0, #0x81c]
	str r2, [r0, #0x820]
	str r2, [r0, #0x824]
	str r2, [r0, #0x828]
	str r2, [r1, #0x81c]
	str r2, [r1, #0x820]
	str r2, [r1, #0x824]
	str r2, [r1, #0x828]

	ldr r2, =0x00000800
	str r2, [r0, #0x8b8]
	str r2, [r1, #0x8b8]

	ldr r2, =0x0002002D
	str r2, [r0, #0x004]
	ldr r2, =0x00333040
	str r2, [r0, #0x008]

	ldr r2, =0x3F4352F3
	str r2, [r0, #0x00c]
	ldr r2, =0xB66D8B63
	str r2, [r0, #0x010]

	ldr r2, =0x01FF00DB
	str r2, [r0, #0x014]
	ldr r2, =0x00011740
	str r2, [r0, #0x018]

	ldr r2, =0x00008000
	str r2, [r0, #0x01c]
	ldr r2, =0x000026d2
	str r2, [r0, #0x02c]
	ldr r2, =0x00431023
	str r2, [r0, #0x030]
	ldr r2, =0x00000027
	str r2, [r0, #0x040]

	ldr r2, =0x831A0000
	str r2, [r0, #0x000]

	ldr r2, =0x02008032
	str r2, [r0, #0x01c]
	ldr r2, =0x00008033
	str r2, [r0, #0x01c]
	ldr r2, =0x00048031
	str r2, [r0, #0x01c]
	ldr r2, =0x15208030
	str r2, [r0, #0x01c]
	ldr r2, =0x04008040
	str r2, [r0, #0x01c]

	ldr r2, =0x00007800
	str r2, [r0, #0x020]
	ldr r2, =0x00022227
	str r2, [r0, #0x818]
	str r2, [r1, #0x818]
	ldr r2, =0x0002556D
	str r2, [r0, #0x004]
	ldr r2, =0x00011006
	str r2, [r0, #0x404]
	ldr r2, =0x00000000
	str r2, [r0, #0x01c]
.endm

.macro imx6solo_iwg15m_ddr_setting
	ldr r0, =IOMUXC_BASE_ADDR
	ldr r1, =0x000c0000
	str r1, [r0, #0x774]
	ldr r1, =0x00000000
	str r1, [r0, #0x754]

	ldr r1, =0x00000030
	str r1, [r0, #0x4ac]
	str r1, [r0, #0x4b0]
	str r1, [r0, #0x464]
	str r1, [r0, #0x490]
	str r1, [r0, #0x74c]
	str r1, [r0, #0x494]

	ldr r1, =0x00000000
	str r1, [r0, #0x4a0]

	ldr r1, =0x00000030
	str r1, [r0, #0x4b4]
	str r1, [r0, #0x4b8]
	str r1, [r0, #0x76c]

	ldr r1, =0x00020000
	str r1, [r0, #0x750]

	ldr r1, =0x00000030
	str r1, [r0, #0x4bc]
	str r1, [r0, #0x4c0]
	str r1, [r0, #0x4c4]
	str r1, [r0, #0x4c8]

	ldr r1, =0x00020000
	str r1, [r0, #0x760]

	ldr r1, =0x00000030
	str r1, [r0, #0x764]
	str r1, [r0, #0x770]
	str r1, [r0, #0x778]
	str r1, [r0, #0x77c]
	str r1, [r0, #0x470]
	str r1, [r0, #0x474]
	str r1, [r0, #0x478]
	str r1, [r0, #0x47c]

	ldr r0, =MMDC_P0_BASE_ADDR
	ldr r2, =0x00008000
	str r2, [r0, #0x01c]
	ldr r2, =0xa1390003
	str r2, [r0, #0x800]

	ldr r2, =0x0042004C
	str r2, [r0, #0x80c]
	ldr r2, =0x0035003F
	str r2, [r0, #0x810]

	ldr r2, =0x02400244
	str r2, [r0, #0x83c]
	ldr r2, =0x022C022C
	str r2, [r0, #0x840]

	ldr r2, =0x464A4E4C
	str r2, [r0, #0x848]

	ldr r2, =0x38343032
	str r2, [r0, #0x850]

	ldr r2, =0x33333333
	str r2, [r0, #0x81c]
	str r2, [r0, #0x820]
	str r2, [r0, #0x824]
	str r2, [r0, #0x828]

	ldr r2, =0x00000800
	str r2, [r0, #0x8b8]

	ldr r2, =0x0002002D
	str r2, [r0, #0x004]
	ldr r2, =0x00333040
	str r2, [r0, #0x008]

	ldr r2, =0x3F4352F3
	str r2, [r0, #0x00c]
	ldr r2, =0xB66D8B63
	str r2, [r0, #0x010]

	ldr r2, =0x01FF00DB
	str r2, [r0, #0x014]
	ldr r2, =0x00011740
	str r2, [r0, #0x018]

	ldr r2, =0x00008000
	str r2, [r0, #0x01c]
	ldr r2, =0x000026d2
	str r2, [r0, #0x02c]
	ldr r2, =0x00431023
	str r2, [r0, #0x030]
	ldr r2, =0x00000027
	str r2, [r0, #0x040]

	ldr r2, =0x83190000
	str r2, [r0, #0x000]

	ldr r2, =0x02008032
	str r2, [r0, #0x01c]
	ldr r2, =0x00008033
	str r2, [r0, #0x01c]
	ldr r2, =0x00048031
	str r2, [r0, #0x01c]
	ldr r2, =0x15208030
	str r2, [r0, #0x01c]
	ldr r2, =0x04008040
	str r2, [r0, #0x01c]

	ldr r2, =0x00007800
	str r2, [r0, #0x020]
	ldr r2, =0x00022227
	str r2, [r0, #0x818]
	ldr r2, =0x0002556D
	str r2, [r0, #0x004]
	ldr r2, =0x00011006
	str r2, [r0, #0x404]
	ldr r2, =0x00000000
	str r2, [r0, #0x01c]
.endm
.macro imx6_clock_gating
	ldr r0, =CCM_BASE_ADDR
	ldr r1, =0x00C03F3F
	str r1, [r0, #0x068]
	ldr r1, =0x0030FC03
	str r1, [r0, #0x06c]
	ldr r1, =0x0FFFC000
	str r1, [r0, #0x070]
	ldr r1, =0x3FF00000
	str r1, [r0, #0x074]
	ldr r1, =0x00FFF300
	str r1, [r0, #0x078]
	ldr r1, =0x0F0000F3
	str r1, [r0, #0x07c]
	ldr r1, =0x000003FF
	str r1, [r0, #0x080]
.endm

.macro imx6_qos_setting
	ldr r0, =IOMUXC_BASE_ADDR
	ldr r1, =0xF00000CF
	str r1, [r0, #0x10]

	ldr r1, =0x007F007F
	str r1, [r0, #0x18]
	str r1, [r0, #0x1c]
.endm

.macro imx6_ddr_setting
	ldr r0, =ANATOP_BASE_ADDR
	ldr r1, [r0,#0x260]
	ldr r3,=0xff0000
	and r1,r1,r3
	cmp r1,#0x630000
	beq quad_cpu

	ldr r0, =OCOTP_BASE_ADDR
	ldr r1, [r0,#0x430]
	ldr r3,=0x100000
	and r1,r1,r3
	cmp r1,#0x100000
	beq solo_cpu	
	cmp r1,#0x0
	beq duallite_cpu

solo_cpu:
	imx6solo_iwg15m_ddr_setting
	b common_ddr

duallite_cpu:
	imx6dl_iwg15m_ddr_setting
	b common_ddr

quad_cpu:
	imx6dq_iwg15m_ddr_setting
	b common_ddr

common_ddr:
.endm

/* include the common plugin code here */
#include <asm/arch/mx6_plugin.S>
