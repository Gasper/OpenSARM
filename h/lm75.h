/**
 * @file lm75.h
 * @author Matjaž Tome
 * @brief I<sup>2</sup>C knjižnjica za temperaturni senzor
 */

#ifndef LM75_H_INCLUDED
#define LM75_H_INCLUDED

/// I<sup>2</sup>C naslov senzorja na OpenŠARM razvojni plošči
#define LM75_ADR 0x91

/**
 * Nastavi i2c0 za delovanje z LM75 temperaturnim senzorjem
 *
 * @param clk Želena i2c0 frekvenca ure v Hz
 */
void lm75_init (unsigned int clk);

/**
 * Vrne neobdelane podatke s senzorja
 *
 * @param adr Naslov senzorja
 * @return Podatki s senzorja
 */
signed int lm75_get_temp_raw (unsigned char adr);

/**
 * Vrne temperaturo s senzorja v °C (celi del in decimalni del posebej)
 *
 * @param adr Naslov senzorja
 * @param *w Kazalec na spremenljivko, kjer bo shranjen celi del
 * @param *d Kazalec na spremenljivko, kjer bo shranjen decimalni del
 */
void lm75_get_temp (unsigned char adr, signed char *w, signed char *d);

#ifdef ONLY_USED
#include "lm75.c"
#endif

#endif
