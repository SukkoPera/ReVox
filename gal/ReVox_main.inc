/* ReVox GAL Equations
 * Copyright 2023 SukkoPera <software@sukkology.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/* These equations can be turned into a JED file through the WinCUPL software.
 * Too bad it's Windows-only and full of bugs...
 */

/* Address: $FD5E + FE9E, the address for the Digiblaster on SIDcards.
 */

/** Inputs **/
Pin 1 = a15;
Pin 2 = a14;
Pin 3 = a13;
Pin 4 = a12;
Pin 5 = a11;
Pin 6 = a10;
Pin 7 = a8;
Pin 8 = a6;
Pin 9 = a4;
Pin 10 = a2;
Pin 11 = a0;
Pin 15 = a1;
Pin 16 = a3;
Pin 17 = a5;
Pin 18 = a7;
Pin 19 = a9;

Pin 14 = phi2;
Pin 22 = rw;
Pin 23 = reset;				// Active-low

/** Outputs **/
Pin 20 = clock;				// 74x273 clock, data is sampled on rising edge
Pin 21 = clear;				// 74x273 clear, active-low

/** Declarations and Intermediate Variable Definitions **/
Field addr = [a15..0];


/** Logic Equations **/

/* 6502 write cycle works as follows:
 * 0. PHI2 starts low, R/W starts high (R)
 * 1. Address is put on the address bus
 * 2. R/W goes low, signalling write cycle
 * 3. PHI2 goes high, signalling address valid
 * 4. Data is put on the data bus
 * 5. PHI2 goes low, signalling data valid
 * 6. Cycle ends
 * 
 * Now, we need to generate a RISING edge when we are addressed and data is valid, so:
 * - We idle HIGH
 * - We go low when R/W is low (W) and our address is validated on the bus (i.e.: on the rising edge of PHI2)
 * - We go back to high on the falling edge of PHI2, which marks data valid
 */ 
_de_addr = addr:FD5E;
_hu_addr = addr:FE9E;
clock = !(!rw & (_de_addr # _hu_addr) & phi2);

clear = reset;				// Both signals are active-low
