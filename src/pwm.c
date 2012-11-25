/**
 * 2012 OpenSARM
 * Avtor: Jernej Sorta <jernejsorta@gmail.com>
 *
 */

/*

Konstanta DELEZ predstavlja odstotno izražanje, torej kjer se prevajalno razmerje piše v %, jih v bistvu pišemo kot odstotek od DELEZ. Na primer, če je DELEZ=1000
in želimo prevajalno razmerje 50:50, potem moramo za prevajalno razmerje zapisati 500. Če je DELEZ 100 pišemo 50, če je 10 pišemo 5 itd.
DELEZ nam določa ločljivost.

Opomba:
Manjka še možnost neposrednega nastavljanja primerjalnih registrov PWMMR0-6, za potrebo drugih časovnih funkcij. Sedaj je to možno nastavljati posredno
preko nastavitve kanala.

 */

#include "lpc214x.h"
#include "pwm.h"
#include "io.h"

void timer_state(unsigned char state)
{
	switch (state)
	{
		case STOP_COUNTER:
			//Counter enable, PWM enable pobrisana
			PWM_TCR &= ~((1 << COUNTER_ENABLE) || (1 << PWM_ENABLE));
			break;
		case START_COUNTER:
			// postavljena Counter Enable in PWM Enable
			PWM_TCR |= (1 << COUNTER_ENABLE) || (1 << PWM_ENABLE);
			//pobrisan counter reset
			PWM_TCR &= ~(1 << COUNTER_RESET);
			break;
		case RESET_COUNTER:
			//števec ponastavimo in ga nato spet poženemo
			PWM_TCR |= (1 << COUNTER_RESET);
			//kratka zakasnitev...verjetno ni nujno potrebna
			unsigned char pwmreset_counter;
			for (pwmreset_counter = 0 ;pwmreset_counter < 10; pwmreset_counter++);

			PWM_TCR &= ~(1 << COUNTER_RESET);
			break;
	}
}

void pwm_set_frequency(unsigned int frequency)//unsigned long? potrebno za številke načeloma do 60M->do kje gre unsigned int? 32bit?
{
	//Zaenkrat še ni podpore za preddelilnik takta za PWM. CPU_FREQ je določen v lpc214x.h
	PWM_MR0 = (CPU_FREQ * 1000 / frequency);
	//Ko štecev prešteje do PWM_MR0 se ponastavi, s tem dolčimo frekvenco
	PWMMCR |= (1 << PWMMR0R);
	//V latch enable registru omogočimo, da se vrednost iz PWM_MR0 prenese iz senčnega registra v pravi register, ko se števec ponastavi
	PWM_LER |= (1 << PWM0);
}

unsigned char pwm_set_channel(unsigned char channel/*od PWM1-PWM6*/, unsigned char prevajalno_razmerje/*od 0-DELEZ*/, unsigned char vklop/*0 ali 1*/)//vklop je samo, če ne bi hoteli speljati PWM na izhode
{
	#ifdef __PWM_DVOJNI_BOK__
	return 0;
	#endif

	#define __PWM_ENONJNI_BOK__

	unsigned char stevilka_kanala = channel;

	//V primeru, da bi bila številka kanala neveljavna
	if (channel > 6)
		stevilka_kanala = 6;
	else if (channel < 1)
		stevilka_kanala = 1;

	/*
	Preverjanje, če je prevajalno razmerje večje od DELEZ ni potrebno, ker je popravek že strojno opravljen.
	V tem primeru je izhod vedno na "1"
	*/

	switch (stevilka_kanala)
	{
		case PWM1:
			//Če je vklop=="1", potem je PWM fja omogočena in speljana na izhod
			if (vklop)
			{
				PWM_MR1 = (PWM_MR0 / DELEZ) * prevajalno_razmerje;
				//ALI operacija ni potrebna, saj določimo vsakič posebej, kateri kanal želimo. Potem se vsakič vsi biti samodejno pobrišejo
				PWM_LER = (1 << PWM1);
				//omogočimo PWM1 izhod
				PWM_PCR |= (1 << PWMENA1);
				//Določimo P0.0 kot izhod
				IODIR0 |= (IZHOD << PIN0);
				//Sponki P0.0 določimo fjo PWM, ki ima številko 2 (tretja po vrsti)
				PINSEL0 |= (FUN_2 << (PIN0 * 2));
			}
			else //če je vklop=="0", potem je PWM fja onemogočena, vendar utegne še vedno biti speljana na izhod, če smo to kdaj storili
			{
				//onemogočimo PWM1 izhod
				PWM_PCR &= ~(1 << PWMENA1);
			}

			break;

			case PWM2:
				if (vklop)
				{
					PWM_MR2 = (PWM_MR0 / DELEZ) * prevajalno_razmerje;
					PWM_LER = (1 << PWM2);
					PWM_PCR |= (1 << PWMENA2);
					IODIR0 |= (IZHOD << PIN7);
					PINSEL0 |= (FUN_2 << (PIN7 * 2));
				}
				else
				{
					PWM_PCR &= ~(1 << PWMENA2);
				}
				break;

			case PWM3:
				if (vklop)
				{
					PWM_MR3 = (PWM_MR0 / DELEZ) * prevajalno_razmerje;
					PWM_LER = (1 << PWM3);
					PWM_PCR |= (1 << PWMENA3);
					IODIR0 |= (IZHOD << PIN1);
					PINSEL0 |= (FUN_2 << (PIN1 * 2));
				}
				else
				{
					PWM_PCR &= ~(1 << PWMENA3);
				}
				break;

			case PWM4:
				if (vklop)
				{
					PWM_MR4 = (PWM_MR0 / DELEZ) * prevajalno_razmerje;
					PWM_LER = (1 << PWM4);
					PWM_PCR |= (1 << PWMENA4);
					IODIR0 |= (IZHOD << PIN8);
					PINSEL0 |= (FUN_2 << (PIN8 * 2));
				}
				else
				{
					PWM_PCR &= ~(1 << PWMENA4);
				}
				break;

			case PWM5:
				if (vklop)
				{
					PWM_MR5 = (PWM_MR0 / DELEZ) * prevajalno_razmerje;
					PWM_LER = (1 << PWM5);
					PWM_PCR |= (1 << PWMENA5);
					IODIR0 |= (IZHOD << PIN21);
					PINSEL1 |= (FUN_1 << 10);
				}
				else
				{
					PWM_PCR &= ~(1 << PWMENA5);
				}
				break;

			case PWM6:
				if (vklop)
				{
					PWM_MR6 = (PWM_MR0 / DELEZ) * prevajalno_razmerje;
					PWM_LER = (1 << PWM6);
					PWM_PCR |= (1 << PWMENA6);
					IODIR0 |= (IZHOD << PIN9);
					PINSEL0 |= (FUN_2 << (PIN9 * 2));
				}
				else
				{
					PWM_PCR &= ~(1 << PWMENA6);
				}
			break;
	}
}

void pwm_reset_interrupt(unsigned char channel)	//ponastavimo prekinitev
{
	//Za ponastavitev prekinitve moramo v PWM_IR vpisat "1" na željeno mesto
	unsigned char stevilka_kanala = channel;
	if (channel > 6)
		stevilka_kanala = 6;

	if ( stevilka_kanala < 4)
		PWM_IR |= (1 << stevilka_kanala);
	else
		//V registru biti ne gredo po vrsti, ampak je med PWMMR3 in PWMMR4 praznina za 4 bite.
		PWM_IR |= (1<<(stevilka_kanala + 4));
}

/*S to fjo lahko nastavimo dogodek, ki se zgodi, ko vrednost števca doseže vrednost v PWMMRx.
Za običajno rabo ni potreno nastavljati ničesar.
Izbiramo lahko med prekinitvijo, ustavitvijo števca, ali ponastavitvijo števca->števec gre na 0 in tam ostane?
Če števec ustavimo ali ponastavimo, ga je potrebno spet zagnat s fjo Casovnik_Stanje(ZAZENI_STEVEC)
*/
void pwm_set_event(unsigned char channel, unsigned char event)
{
	//V primeru, da bi bila številka kanala neveljavna
	unsigned char channel_number = channel;
	if (channel > 6)
		channel_number = 6;

	unsigned char real_event = event;

	//V primeru neveljavnega dogodka:
	if (event <= (PREKINITEV | USTAVITEV | PONASTAVITEV))
		//Z fjo ALI lahko izberemo več dogodkov, npr: Za ponastavitev in ustavitev damo za argument "dogodek": USTAVITEV|PONASTAVITEV
		real_event = event;
	else
		real_event = 0;

	//najprej pobrišemo prejšnje stanje
	PWMMCR &= ~((PREKINITEV | USTAVITEV | PONASTAVITEV) << channel_number);
	//in nato zapišemo novega
	PWMMCR |= (real_event << channel_number);
}

/*
 * V tej fji so možni PWM izhodi PWM2, PWM4 in PWM6. To pa zato, da se doseže res neodvisno postavitev sunka.
Lahko bi bili tudi PWM1, PWM3, PWM5, oziroma še neke mešanke med njimi.
V primeru napačnih argumentov fja vrne 0, sicer pa 1

Opomba: ->lahko bi bila unsigned char?
*/
unsigned int PWM_DvojniBok(unsigned char pwm_izhod, unsigned int zacetek_sunka, unsigned int konec_sunka, unsigned char vklop)
{
#ifdef __PWM_ENONJNI_BOK__
return 0;
#endif

#define __PWM_DVOJNI_BOK__

	//v primeru neveljavnega PWM izhoda
	unsigned char pravi_pwm_izhod;
	if (pwm_izhod > 6)
		pravi_pwm_izhod = 6;
	else
		pravi_pwm_izhod = pwm_izhod;

	if (!((pwm_izhod == PWM2) || (pwm_izhod == PWM4) || (pwm_izhod == PWM6)))
		return 0;

  switch(pravi_pwm_izhod)
  {
    case PWM2:
      if(vklop)
      {
      PWM_PCR |= (1<<PWMSEL2)|(PWMENA2);
      PWM_MR1 = (PWM_MR0/DELEZ)*(zacetek_sunka < konec_sunka ? zacetek_sunka : konec_sunka);//za vsak slučaj, če bi kdo zamešal začetek in konec je najmanjša vrednost vedno začetek in največja vrednost vedno konec sunka
      PWM_MR2 = (PWM_MR0/DELEZ)*(zacetek_sunka > konec_sunka ? zacetek_sunka : konec_sunka);
      PWM_LER = (1<<PWM2)|(1<<PWM1);
      IODIR0 |=(IZHOD<<PIN7);
      PINSEL0 |=(FUN_2<<(PIN7*2));
      }
      else
      {
	PWM_PCR &= ~(1<<PWMENA2);
      }
    break;

    case PWM4:
      if(vklop)
      {
	PWM_PCR |= (1<<PWMSEL4)|(PWMENA4);
	PWM_MR3 = (PWM_MR0/DELEZ)*(zacetek_sunka < konec_sunka ? zacetek_sunka : konec_sunka);//za vsak slučaj, če bi kdo zamešal začetek in konec je najmanjša vrednost vedno začetek in največja vrednost vedno konec sunka
	PWM_MR4 = (PWM_MR0/DELEZ)*(zacetek_sunka > konec_sunka ? zacetek_sunka : konec_sunka);
	PWM_LER = (1<<PWM4)|(1<<PWM3);
	IODIR0 |=(IZHOD<<PIN8);
	PINSEL0 |=(FUN_2<<(PIN8*2));
      }
      else
      {
	PWM_PCR &= ~(1<<PWMENA4);
      }
    break;

    case PWM6:
      if(vklop)
      {
	PWM_PCR |= (1<<PWMSEL6)|(PWMENA6);
	PWM_MR5 = (PWM_MR0/DELEZ)*(zacetek_sunka < konec_sunka ? zacetek_sunka : konec_sunka);//za vsak slučaj, če bi kdo zamešal začetek in konec je najmanjša vrednost vedno začetek in največja vrednost vedno konec sunka
	PWM_MR6 = (PWM_MR0/DELEZ)*(zacetek_sunka > konec_sunka ? zacetek_sunka : konec_sunka);
	PWM_LER = (1<<PWM5)|(1<<PWM6);
	IODIR0 |=(IZHOD<<PIN9);
	PINSEL0 |=(FUN_2<<(PIN9*2));
      }
      else
      {
	PWM_PCR &= ~(1<<PWMENA6);
      }
    break;

    default:
      return 0;
    break;
  }

    return 1;
}

/*
 Fja omogoča krmiljenje 3-faznega brezkrtačnega motorja. S parametrom "frekvenca" nastavljamo frekvenco vrtenja, oziroma frekvenco PWM-ja. S parametrom "prevajalno_razmerje"
 pa določamo prevajalno razmerje sunkov na vseh treh fazah.
 Možne trojke izhodov so PWM2-4-6(kanal_1_2 = KANAL2_4_6), ali PWM1-3-5(kanal_1_2 = KANAL1_3_5.
 S parametrom "mrtvi_cas" nastavljamo mrtvi čas med sunki. Nastavlja se ga v delu glede na konstanto DELEZ (če je DELEZ 100, nastavljamo od 0-100,
 če je 1000 od 0-100 itd...). S parametrom "faza" nastavljamo smer vrtenja (0 ali 1), s prametrom "vklop" pa bodisi vklopimo, bodisi izklopimo vse tri PWM izhode.
 S parametrom
 */

unsigned int PWM_BrezKrtack(unsigned int frekvenca, unsigned int prevajalno_razmerje, unsigned int mrtvi_cas, unsigned char kanal_1_2, unsigned char faza, unsigned char vklop)
{
  /*
   frekvenca->frekvenca celotnega cikla
   prevajalno_razmerje-> prevajalno razmerje ene tretjine periode - mrtvi čas
   faza->če je "1" se motor vrti v eno smer, če je "0" pa v drugo
   vklop->lahko vklopimo ali izklopimo PWM
   */
  #ifdef __PWM_ENONJNI_BOK__
    return 0;
  #endif

  if(mrtvi_cas > prevajalno_razmerje) return 0;
  PWM_NastaviFrekvenco(frekvenca);
  if(kanal_1_2 == KANAL1_3_5)
  {
    if(vklop)
    {
      PWM_PCR |= (1<<PWMENA1)|(1<<PWMSEL3)|(1<<PWMSEL5)|(1<<PWMENA3)|(PWMENA5);

      PWM_MR1 = ((PWM_MR0/3 - (PWM_MR0/3)*(mrtvi_cas/DELEZ)))*prevajalno_razmerje/DELEZ;
      if(faza)
      {
	PWM_MR2 = PWM_MR0/3;
	PWM_MR3 = ((PWM_MR0/3 - (PWM_MR0/3)*(mrtvi_cas/DELEZ)))*prevajalno_razmerje/DELEZ + PWM_MR0/3;

	PWM_MR4 = PWM_MR0*2/3;
	PWM_MR5 = ((PWM_MR0/3 - (PWM_MR0/3)*(mrtvi_cas/DELEZ)))*prevajalno_razmerje/DELEZ + PWM_MR0*2/3;
      }
      else
      {
	PWM_MR4 = PWM_MR0/3;
	PWM_MR5 = ((PWM_MR0/3 - (PWM_MR0/3)*(mrtvi_cas/DELEZ)))*prevajalno_razmerje/DELEZ + PWM_MR0/3;

	PWM_MR2 = PWM_MR0*2/3;
	PWM_MR3 = ((PWM_MR0/3 - (PWM_MR0/3)*(mrtvi_cas/DELEZ)))*prevajalno_razmerje/DELEZ + PWM_MR0*2/3;
      }

    }
    else
      {
	PWM_PCR &= ~((1<<PWMENA1)|(1<<PWMENA3)|(PWMENA5));
      }


  }
  else if(kanal_1_2 == KANAL2_4_6)
  {
    if(vklop)
    {
    PWM_DvojniBok(PWM2, 0, ((PWM_MR0/3 - (PWM_MR0/3)*(mrtvi_cas/DELEZ)))*prevajalno_razmerje/DELEZ, vklop);

    if(faza)
      {
	PWM_DvojniBok(PWM4, PWM_MR0/3, ((PWM_MR0/3 - (PWM_MR0/3)*(mrtvi_cas/DELEZ)))*prevajalno_razmerje/DELEZ + PWM_MR0/3, vklop);
	PWM_DvojniBok(PWM6, PWM_MR0*2/3, ((PWM_MR0/3 - (PWM_MR0/3)*(mrtvi_cas/DELEZ)))*prevajalno_razmerje/DELEZ + PWM_MR0*2/3, vklop);
      }
      else
      {
	PWM_DvojniBok(PWM6, PWM_MR0/3, ((PWM_MR0/3 - (PWM_MR0/3)*(mrtvi_cas/DELEZ)))*prevajalno_razmerje/DELEZ + PWM_MR0/3, vklop);
	PWM_DvojniBok(PWM4, PWM_MR0*2/3, ((PWM_MR0/3 - (PWM_MR0/3)*(mrtvi_cas/DELEZ)))*prevajalno_razmerje/DELEZ + PWM_MR0*2/3, vklop);
      }
    }
    else
    {
      PWM_PCR &= ~((1<<PWMENA2)|(1<<PWMENA4)|(PWMENA6));
    }

  }
  else return 0;

  return 1;
}


