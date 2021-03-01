// This source is part of the SSK project and thus is licensed under GPL-3.
// Use my code in any way you see fit and if you use it or parts of it please give creddit.
// Disclaimer: I dont provide any warranty that my code functions as intended.
// If my code causes trubbles and you loose all of your data and/or you computer catches fire thats on you!

#ifndef PLATFORM_H
	#define PLATFORM_H

	#include "types.h"

	struct REGISTERS {
		union {
			struct {
				uint32_t D0;
				uint32_t D1;
				uint32_t D2;
				uint32_t D3;
				uint32_t D4;
				uint32_t D5;
				uint32_t D6;
				uint32_t D7;
			};
			uint32_t D[8];
		};
		union {
			struct {
				uint32_t A0;
				uint32_t A1;
				uint32_t A2;
				uint32_t A3;
				uint32_t A4;
				uint32_t A5;
				uint32_t A6;
				union {
					uint32_t A7;
					uint32_t USP;
				};
			};
			uint32_t A[8];
		};
		uint32_t PC;
		uint16_t SR;
	};

	REGISTERS getUserRegisters();
	void setUserRegisters(REGISTERS reg);
	void returnInt();
#endif
