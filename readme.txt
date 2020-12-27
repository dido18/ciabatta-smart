Assorbimento 

Arduino nano solo:                     0.30-0.40 mA
Arduino nano + bluetooth hc06:         0.70-0.90 mA 
Arduino nano + bluetoot hc06 + 4 rele: 4 mA

20% safety margin on the toal ampere

Alimentatore cellulare output DC: 5v, 0.7A (750 mA)


alimentazione asrduino:
  - USB; 5v e corente massimo 250 mA / 500 mA
  - alimentatore esterno: limitata a 500 mA dal PTC (sarebbe 1 o 2 A)
  - presa jsck japan
  - presa Vin:
	1) ingresso: per alimentazione esterna non protetto da cambi di polarita.
        2) uscita da cui perendere la tensione.
  - presa 5V: (sconsigliato usato come ingresso perchè privo di protezioni)
        1) ingresso (quando presa jack o usb non sono collegate): da fonte esterna stabilizzati a 5v. NOn ha protezione.
        2) uscita: prelievo 5v da USB o jack