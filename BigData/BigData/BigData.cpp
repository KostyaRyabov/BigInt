#include "stdafx.h"
#include <iostream>

using namespace std;

struct temp {
	char symb;
	temp* next;
};

class Chislo {
private:
	char* value;
	short znak = 1;
	int kpt = 0;
	int kdt = 0;
public:
	Chislo();
	Chislo(char* input);
	void Set(char* input);
	char* Get();
	friend bool Check(Chislo *obj);
	friend void Invert(Chislo *obj);
	~Chislo();

	friend Chislo& operator+ (Chislo &A, Chislo &B);
	friend Chislo& operator- (Chislo &A, Chislo &B);
	friend Chislo& operator* (Chislo &A, Chislo &B);
	friend Chislo& operator! (Chislo &A);
};

void Destructor(Chislo *Obj) {
	static Chislo *O[2];
	static int i = 0;

	if (O[i] != NULL) {
		delete(O[i]);
	}

	O[i] = Obj;
	i++;

	if (i > 1) {
		i = 0;
	}
}

Chislo& operator- (Chislo &A, Chislo &B) {
	Chislo *Output;
	if ((Check(&A) == 1) && (Check(&B) == 1)) {

		int i;
		char AisLarger = 2;
		char cA, cB;

		bool fA = 0;
		bool fB = 0;

		if ((A.kdt - B.kdt) < 0) {
			AisLarger = 0;
		}
		else if ((A.kdt - B.kdt) > 0) {
			AisLarger = 1;
		}
		else {
			i = 0;
			while ((AisLarger == 2) && (*(A.value + i + ((A.znak == -1) ? 1 : 0)) != '\0') && (*(B.value + i + ((B.znak == -1) ? 1 : 0)) != '\0')) {
				if (*(A.value + i + ((A.znak == -1) ? 1 : 0)) < *(B.value + i + ((B.znak == -1) ? 1 : 0))) {
					AisLarger = 0;
				}
				else if (*(A.value + i + ((A.znak == -1) ? 1 : 0)) > *(B.value + i + ((B.znak == -1) ? 1 : 0))) {
					AisLarger = 1;
				}

				i++;
			}
		}

		Invert(&A);
		Invert(&B);

		char *tempChar = NULL;
		int d = (A.kpt - B.kpt);

		if (d != 0) {
			if (A.kpt == 0) {
				d--;
			}
			else if (B.kpt == 0) {
				d++;
			}
		}

		bool p = 0;
		fA = 0;
		fB = 0;

		temp *pSTART, *pNEW, *pKEPT;

		pSTART = NULL;
		pNEW = NULL;
		pKEPT = NULL;

		if (d >= 0) {
			tempChar = A.value;
			if (((*(tempChar) < 48) || (*(tempChar) > 57)) && (*(tempChar) != 46)) {
				fA = 1;
			}
		}
		if (d <= 0) {
			tempChar = B.value;
			if (((*(tempChar) < 48) || (*(tempChar) > 57)) && (*(tempChar) != 46)) {
				fB = 1;
			}
		}

		i = 0;

		while ((fA == 0) || (fB == 0)) {
			if (d > 0) {
				if ((i < d) || (fB == 1)) {
					cB = 48;
				}
				else {
					tempChar = B.value + i - d;
					cB = *(tempChar);
				}

				if ((i >= d) && (fB == 0)) {
					if (((*(tempChar + 1) < 48) || (*(tempChar + 1) > 57)) && (*(tempChar + 1) != 46)) {
						fB = 1;
					}
				}
				tempChar = A.value + i;
				if (fA == 1) {
					cA = 48;
				}
				if (fA == 0) {
					cA = *(tempChar);
					if (((*(tempChar + 1) < 48) || (*(tempChar + 1) > 57)) && (*(tempChar + 1) != 46)) {
						fA = 1;
					}
				}
			}
			else if (d < 0) {
				if ((i < -d) || (fA == 1)) {
					cA = 48;
				}
				else {
					tempChar = A.value + i + d;
					cA = *(tempChar);
				}

				if ((i >= -d) && (fA == 0)) {
					if (((*(tempChar + 1) < 48) || (*(tempChar + 1) > 57)) && (*(tempChar + 1) != 46)) {
						fA = 1;
					}
				}
				tempChar = B.value + i;
				if (fB == 1) {
					cB = 48;
				}
				if (fB == 0) {
					cB = *(tempChar);
					if (((*(tempChar + 1) < 48) || (*(tempChar + 1) > 57)) && (*(tempChar + 1) != 46)) {
						fB = 1;
					}
				}
			}
			else {
				if (fA == 0) {
					tempChar = A.value + i;
					cA = *(tempChar);
					if (((*(tempChar + 1) < 48) || (*(tempChar + 1) > 57)) && (*(tempChar + 1) != 46)) {
						fA = 1;
					}
				}
				else {
					cA = 48;
				}
				if (fB == 0) {
					tempChar = B.value + i;
					cB = *(tempChar);
					if (((*(tempChar + 1) < 48) || (*(tempChar + 1) > 57)) && (*(tempChar + 1) != 46)) {
						fB = 1;
					}
				}
				else {
					cB = 48;
				}
			}

			pNEW = new temp;

			if (cA == 46 || cB == 46) {
				pNEW->symb = 46;
			}
			else {
				if (A.znak != B.znak) {
					pNEW->symb = (cA + cB - 96 + p) % 10 + 48;

					p = (cA + p + cB - 96 > 9) ? 1 : 0;
				}
				else {
					if (AisLarger != 1) {
						pNEW->symb = (cB - cA + ((cB - p < cA) ? 10 : 0) - p) % 10 + 48;
					}
					else {
						pNEW->symb = (cA - cB + ((cA - p < cB) ? 10 : 0) - p) % 10 + 48;
					}
					if (AisLarger != 1) {
						p = (cB - p < cA) ? 1 : 0;
					}
					else {
						p = (cA - p < cB) ? 1 : 0;
					}
				}
			}

			if (pSTART == NULL) {
				pSTART = pNEW;
			}
			else {
				pKEPT->next = pNEW;
			}
			pKEPT = pNEW;

			i++;
		}

		if (p != 0) {
			pNEW = new temp;
			pNEW->symb = 49;
			pKEPT->next = pNEW;
			i++;
		}

		if ((A.znak == 1 && B.znak == 1 && AisLarger == 0) || (A.znak == -1 && B.znak == -1 && AisLarger == 1) || (A.znak == -1 && B.znak == 1)) {
			pKEPT = new temp;
			pKEPT->symb = '-';
			pNEW->next = pKEPT;
			pNEW = pKEPT;
			i++;
		}

		pNEW->next = NULL;

		int len = i;
		char *value = new char[len];

		i = 0;
		pNEW = pSTART;

		while (pNEW != NULL) { 
			*(value + i) = pNEW->symb;
			pKEPT = pNEW;
			pNEW = pNEW->next;
			delete(pKEPT);
			i++;
		}
		*(value + i) = '\0';

		char c;
		for (i = 0; i < (len / 2); i++) {
			c = *(value + i);
			*(value + i) = *(value + (len - i - 1));
			*(value + (len - i - 1)) = c;
		}

		Invert(&A);
		Invert(&B);

		Output = new Chislo(value);

		Destructor(Output);

		return *Output;
	}
	else {
		Output = new Chislo();

		Destructor(Output);

		return *Output;
	}
}

Chislo& operator+ (Chislo &A, Chislo &B) {
	Chislo *Output;

	if ((Check(&A) == 1) && (Check(&B) == 1)) {

		int i;
		char AisLarger = 2;
		char cA, cB;

		bool fA = 0;
		bool fB = 0;

		if ((A.kdt - B.kdt) < 0) {
			AisLarger = 0;
		}
		else if ((A.kdt - B.kdt) > 0) {
			AisLarger = 1;
		}
		else {
			i = 0;
			while ((AisLarger == 2) && (*(A.value + i + ((A.znak == -1) ? 1 : 0)) != '\0') && (*(B.value + i + ((B.znak == -1) ? 1 : 0)) != '\0')) {
				if (*(A.value + i + ((A.znak == -1) ? 1 : 0)) < *(B.value + i + ((B.znak == -1) ? 1 : 0))) {
					AisLarger = 0;
				}
				else if (*(A.value + i + ((A.znak == -1) ? 1 : 0)) > *(B.value + i + ((B.znak == -1) ? 1 : 0))) {
					AisLarger = 1;
				}
				
				i++;
			}
		}
		
		Invert(&A);
		Invert(&B);

		char *tempChar = NULL;
		int d = (A.kpt - B.kpt);

		if (d != 0) {
			if (A.kpt == 0) {
				d--;
			}
			else if (B.kpt == 0) {
				d++;
			}
		}

		bool p = 0;
		fA = 0;
		fB = 0;

		temp *pSTART, *pNEW, *pKEPT;

		pSTART = NULL;
		pNEW = NULL;
		pKEPT = NULL;
		
		if (d >= 0) {
			tempChar = A.value;
			if (((*(tempChar) < 48) || (*(tempChar) > 57)) && (*(tempChar) != 46)) {
				fA = 1;
			}
		}
		if (d <= 0) {
			tempChar = B.value;
			if (((*(tempChar) < 48) || (*(tempChar) > 57)) && (*(tempChar) != 46)) {
				fB = 1;
			}
		}

		i = 0;

		while ((fA==0) || (fB==0)) {
			if (d > 0) {
				if ((i < d) || (fB == 1)) {
					cB = 48;
				}else{
					tempChar = B.value + i - d;
					cB = *(tempChar);
				}

				if ((i >= d) && (fB == 0)){
					if (((*(tempChar + 1) < 48) || (*(tempChar + 1) > 57)) && (*(tempChar + 1) != 46)) {
						fB = 1;
					}
				}
				tempChar = A.value + i;
				if (fA == 1) {
					cA = 48;
				}
				if (fA == 0){
					cA = *(tempChar);
					if (((*(tempChar + 1) < 48) || (*(tempChar + 1) > 57)) && (*(tempChar + 1) != 46)) {
						fA = 1;
					}
				}
			}
			else if (d < 0) {
				if ((i < -d) || (fA == 1)) {
					cA = 48;
				}
				else {
					tempChar = A.value + i + d;
					cA = *(tempChar);
				}

				if ((i >= -d) && (fA == 0)) {
					if (((*(tempChar + 1) < 48) || (*(tempChar + 1) > 57)) && (*(tempChar + 1) != 46)) {
						fA = 1;
					}
				}
				tempChar = B.value + i;
				if (fB == 1) {
					cB = 48;
				}
				if (fB == 0) {
					cB = *(tempChar);
					if (((*(tempChar + 1) < 48) || (*(tempChar + 1) > 57)) && (*(tempChar + 1) != 46)) {
						fB = 1;
					}
				}
			}
			else{
				if (fA == 0) {
					tempChar = A.value + i;
					cA = *(tempChar);
					if (((*(tempChar + 1) < 48) || (*(tempChar + 1) > 57)) && (*(tempChar + 1) != 46)) {
						fA = 1;
					}
				}
				else {
					cA = 48;
				}
				if (fB == 0) {
					tempChar = B.value + i;
					cB = *(tempChar); 
					if (((*(tempChar + 1) < 48) || (*(tempChar + 1) > 57)) && (*(tempChar + 1) != 46)) {
						fB = 1;
					}
				}
				else {
					cB = 48;
				}
			}

			pNEW = new temp;

			if (cA == 46 || cB == 46) {
				pNEW->symb = 46;
			}
			else {
				int Result;

				if (A.znak != B.znak) {
					if (A.znak == -1) {
						if (AisLarger != 1) {
							pNEW->symb = (cB - cA + ((cB - p < cA) ? 10 : 0) - p) % 10 + 48;
						}
						else {
							pNEW->symb = (cA - cB + ((cA - p < cB) ? 10 : 0) - p) % 10 + 48;
						}

						if (AisLarger != 1) {
							p = (cB - p < cA) ? 1 : 0;
						}
						else {
							p = (cA - p < cB) ? 1 : 0;
						}
					}
					else {
						if (AisLarger != 1) {
							pNEW->symb = (cB - cA + ((cB - p < cA) ? 10 : 0) - p) % 10 + 48;
						}
						else {
							pNEW->symb = (cA - cB + ((cA - p < cB) ? 10 : 0) - p) % 10 + 48;
						}

						if (AisLarger != 1) {
							p = (cB - p < cA) ? 1 : 0;
						}
						else {
							p = (cA - p < cB) ? 1 : 0;
						}
					}
				}
				else {
					Result = cA + cB - 96 + p;

					pNEW->symb = Result % 10 + 48;
					p = Result/10;
				}
			}

			if (pSTART == NULL) {
				pSTART = pNEW;
			}
			else {
				pKEPT->next = pNEW;
			}
			pKEPT = pNEW;

			i++;
		}

		if (p != 0) {
			pNEW = new temp;
			pNEW->symb = 49;
			pKEPT->next = pNEW;
			i++;
		}

		if ((A.znak == -1 && B.znak == 1 && AisLarger == 1) || (A.znak == 1 && B.znak == -1 && AisLarger == 0) || (A.znak == -1 && B.znak == -1)) {
			pKEPT = new temp;
			pKEPT->symb = '-';
			pNEW->next = pKEPT;
			pNEW = pKEPT;
			i++;
		}

		pNEW->next = NULL;

		int len = i;
		char *value = new char[len];

		i = 0;
		pNEW = pSTART;

		while (pNEW != NULL) {
			*(value + i) = pNEW->symb;
			pKEPT = pNEW;
			pNEW = pNEW->next;
			delete(pKEPT);
			i++;
		}
		*(value + i) = '\0';
		
		char c;
		for (i = 0; i < (len / 2); i++) {
			c = *(value + i);
			*(value + i) = *(value + (len - i - 1));
			*(value + (len - i - 1)) = c;
		}

		Invert(&A);
		Invert(&B);

		Output = new Chislo(value);

		Destructor(Output);

		return *Output;
	}
	else {
		Output = new Chislo();

		Destructor(Output);

		return *Output;
	}
}

Chislo& operator* (Chislo &A, Chislo &B) {
	Chislo *Output;
	if ((Check(&A) == 1) && (Check(&B) == 1) && ((*A.value != 48) || (*B.value != 48))) {
		Invert(&A);
		Invert(&B);
		
		int i, j, n, l, R;
		char p;

		int NA = A.kdt + A.kpt;
		int NB = B.kdt + B.kpt;

		int N = NA + NB - 1;

		temp *pSTART, *pNEW, *pKEPT;
		pNEW = NULL;;
		pKEPT = NULL;
		pSTART = NULL;

		n = 0;
		p = 0;
		i = 0;
		j = 0;
		l = 0;

		bool point = false;

		while (n < N) {
			pNEW = new temp;
			if (NA < NB) {
				if (n < NA) {
					i = 0;
					j = n;
				}
				else if ((n >= NA) && (n < NB)) {
					i = n - NA + 1;
					j = N - NB;
				}
				else if (n >= NB) {
					i = n - NA + 1;
					j = N - NB;
					l++;
				}
				if ((n == (A.kpt + B.kpt)) && ((A.kpt + B.kpt) != 0)) l--;
			}
			else {
				if (n < NB) {
					i = 0;
					j = n;
				}
				else if ((n >= NB) && (n < NA)) {
					i = 0;
					j = n;
					l++;
				}
				else if (n >= NA) {
					if (((A.kpt + B.kpt) != 0) && (n == NA)) l--;
					i = n - NA + 1;
					j = N - NB;
					l++;
				}
			}

			if (i >= B.kpt && B.kpt != 0) {
				i++;
			}
			if (j >= A.kpt && A.kpt != 0) {
				j++;
			}
			R = 0;
			while (i <= (n - l)) {
					if (i == B.kpt && B.kpt != 0) {
					i++;
				}
				if (j == A.kpt && A.kpt != 0) {
					j--;
				}
				R += (*(A.value + j) - 48) * (*(B.value + i) - 48);
				j--;
				i++;
			}

			R += p;
			pNEW->symb = R % 10 + 48;
			p = R / 10;
			
			if (pSTART == NULL) {
				pSTART = pNEW;
			}
			else {
				pKEPT->next = pNEW;
			}
			pKEPT = pNEW;

			n++;
		}

		if (p != 0) {
			pNEW = new temp;
			pNEW->symb = p + 48;
			pKEPT->next = pNEW;
			pKEPT = pNEW;
			N++;
		}

		if (A.znak != B.znak) {
			pNEW = new temp;
			pNEW->symb = 45;
			pKEPT->next = pNEW;
			N++;
		}

		pNEW->next = NULL;

		char *value = new char[N];

		i = 0;
		pNEW = pSTART;

		while (pNEW != NULL) { 
			if ((i == (A.kpt + B.kpt)) && ((A.kpt + B.kpt) != 0)) {
				*(value + i) = 46;
				i++;
			}

			*(value + i) = pNEW->symb;
			pKEPT = pNEW;
			pNEW = pNEW->next;
			delete(pKEPT);
			i++;
		}
		*(value + i) = '\0';

		if ((A.kpt + B.kpt) != 0) {
			N++;
		}

		char c;
		for (i = 0; i < (N / 2); i++) {
			c = *(value + i);
			*(value + i) = *(value + (N - i - 1));
			*(value + (N - i - 1)) = c;
		}
		
		Invert(&A);
		Invert(&B);

		Output = new Chislo(value);

		Destructor(Output);

		return *Output;
	}
	else {
		Output = new Chislo();

		Destructor(Output);

		return *Output;
	}
}

Chislo& operator! (Chislo &A) {
	Chislo *output = new Chislo();

	if (Check(&A) == 1) {
		char *one = new char[2];
		Chislo *B = new Chislo();
		
		*one = 49;
		*(one + 1) = '\0';
		
		if (A.znak == -1) {
			B->Set(A.value + 1);
		}
		else {
			B->Set(A.value);
		}

		Chislo *O = new Chislo(one);
		output->Set(A.value);
		
		Check(B);
		Check(output);

		while ((*B->value > 49) || (B->kdt != 1)) {
			*B = *B - *O;
			Check(B);
			*output = *output * *B;
		}
		delete (B);
		delete (O);
		delete (one);
		return *output;
	}
	else {
		return *output;
	}

}

bool Check(Chislo *obj) {
	int i = 0;
	int pp = 0;
	short point = 0;
	char c;
	int zeroCounter = 0;
	bool f = 0;
	bool f1 = 0;
	int zpt = 0;

	obj->kdt = 0;
	obj->kpt = 0;

	while ((c = *(obj->value + i)) != '\0') {
		
		if (((c == 44) || (c == 46))) {
			if (c == 44) {
				c = 46;
			}
			point++;
			pp = i;
			f1 = 1;
			
			if (point > 1) {
				cout << "Error!" << endl;
				return false;
			}
		}
		else if (c == 45) {
			if (i == 0) {
				obj->znak = -1;
			}
			else {
				cout << "Error!" << endl;
				return false;
			}
		}
		else if (c == 43) {
			if (i == 0) {
				obj->znak = +1;
				f = 1;
			}
			else {
				cout << "Error!" << endl;
				return false;
			}
		}
		else if ((c == 48) && (f1 == 0)) {
			zeroCounter++;
		}
		else if (c == 48 && point == 1 && zpt == 0) {
			zpt = i;
		}
		else if ((c < 48) || (c > 57)) {
			cout << "Error!" << endl;
			return false;
		}
		else {
			if (zpt != 0 && point == 1 && c != 48) {
				zpt = 0;
			}
			f1 = 1;
		}

		if (point == 0) {
			obj->kdt++;
		}

		i++;
	}

	if (obj->znak == -1) {
		obj->kdt--;
	}

	obj->kpt = ((pp!=0)?(i-pp-1):0);

	if ((i == 1) && ((c==45) || (c==43))) {
		char str[] = "0";

		obj->Set(str);
		obj->znak = +1;
	}
	else {
		if (f1 == 1) {
			if (point != 0) {
				if (obj->znak == -1) {
					zeroCounter -= ((pp - zeroCounter == 1) ? 1 : 0);
					*(obj->value + zeroCounter) = 45;
				}else if (obj->znak == 1) {
					if (f == 0) {
						zeroCounter -= (pp - zeroCounter == 0) ? 1 : 0;
					}
					else {
						zeroCounter += ((pp - zeroCounter == 1) ? 1 : 0);
					}
				}
			}

			if (zpt != 0) {
				*(obj->value + zpt - ((zpt - 1 == pp)?1:0)) = '\0';
			}
			else {
				if (obj->znak == 1) {
					if (f == 1) {
						zeroCounter++;
					}
				}
				else {
					*(obj->value + zeroCounter) = 45;
				}
			}
		}
		else {
			if (f == 0 && obj->znak == 1) {
				zeroCounter--;
			}
		}
		obj->kdt -= zeroCounter;
		obj->Set(obj->value + zeroCounter);
	}

	return true;
}

void Invert(Chislo *obj) {
	int i;
	int len = 0;
	char c;
	while (*(obj->value + len) != '\0') {
		len++;
	}

	for (i = 0; i < (len / 2); i++) {
		c = *(obj->value + i);
		*(obj->value + i) = *(obj->value + (len - i - 1));
		*(obj->value + (len - i - 1)) = c;
	}
}

void Writer(Chislo *A, Chislo *B, int *operation) {
	int pa = -1;
	int pb = -1;
	
	*operation = 0;
	
	int i = 0;
	temp *pNEW, *pSTART, *pKEPT;

	pNEW = NULL;
	pSTART = NULL;
	pKEPT = NULL;

	char c = getchar();

	while (c != 10) {
		pNEW = new temp;
		pNEW->symb = c;

		if (pSTART == NULL) {
			pSTART = pNEW;
		}
		else {
			pKEPT->next = pNEW;
		}
		pKEPT = pNEW;

		i++;
		c = getchar();
	}

	if (i == 0) {
		pNEW = new temp;
		pNEW->symb = 48;
		pSTART = pNEW;
		i++;
	}

	pNEW->next = NULL;

	char *str = new char[i + 1];

	i = 0;
	pNEW = pSTART;

	while (pNEW != NULL) {
		*(str + i) = pNEW->symb;
		
		pKEPT = pNEW;
		pNEW = pNEW->next;
		delete(pKEPT);
		
		if ((pa != -1) && (*operation != 0) && (pb == -1)) {
			if (*(str + i) != 32) {
				pb = i;
			}
		}
		if ((*operation == 0) && (pa != -1)) {
			if (*(str + i) == '!') {
				*operation = 4;
			}else if (*(str + i) == '-') {
				*operation = 1;
			}else if (*(str + i) == '+') {
				*operation = 2;
			}else if (*(str + i) == '*') {
				*operation = 3;
			}
		}
		if (pa == -1) {
			if (*(str + i) != 32) {
				pa = i;
			}
		}

		if (*(str + i) == 32 || *(str + i) == '!' && !(i == pa || i == pb) || *(str + i) == '*' && !(i == pa || i == pb) || *(str + i) == '-' && !(i == pa || i == pb) || *(str + i) == '+' && !(i == pa || i == pb)) {
			*(str + i) = '\0';
		}

		i++;
	}
	*(str + i) = '\0';

	A->Set(str + pa);
	B->Set(str + pb);

	delete(str);
}

int main() {
	setlocale(0, "");

	int op = 0;
	char enter = 'y';

	static int counter = 1;

	cout << "Введите выражение и нажмите ENTER..." << endl << endl;
	cout << "-------------------------------------------------------------------" << endl;
	while (enter == 'y' || enter == 'Y') {
		Chislo *A = new Chislo();
		Chislo *B = new Chislo();
		Chislo *C = new Chislo();
		
		cout << "  " << counter << " : ";

		Writer(A,B,&op);

		if (op == 0) {
			cout << "Error!" << endl;
		}
		else if (op == 1) {
			*C = *A - *B;
		}
		else if (op == 2) {
			*C = *A + *B;
		}
		else if (op == 3) {
			*C = *A * *B;
		}
		else if (op == 4) {
			*C = !*A;
		}

		Check(C);

		cout << " >>> : ";
		puts(C->Get());

		delete(A);
		delete(B);
		delete(C);

		counter++;
		cout << endl << "Продолжить (Y/N)? ";
		enter = getchar();

		while (enter != 'y' && enter != 'Y' && enter != 'n' && enter != 'N') {
			enter = getchar();
		}

		op = getchar();
		if (op == 10 || op == 32) {
			cout << "-------------------------------------------------------------------" << endl;
		}
	}
}

Chislo::Chislo() {
	value = new char[2];
	*value = '0';
	*(value+1) = '\0';
}

Chislo::Chislo(char* input) {
	int i = 0;
	temp *pNEW, *pSTART, *pKEPT;

	pNEW = NULL;
	pSTART = NULL;
	pKEPT = NULL;

	while (*(input + i) != '\0') {
		pNEW = new temp;
		pNEW->symb = *(input + i);

		if (pSTART == NULL) {
			pSTART = pNEW;
		}
		else {
			pKEPT->next = pNEW;
		}
		pKEPT = pNEW;

		i++;
	}

	pNEW->next = NULL;

	value = new char[i+1];

	i = 0;
	pNEW = pSTART;

	while (pNEW != NULL) { 
		*(value + i) = pNEW->symb;
		pKEPT = pNEW;
		pNEW = pNEW->next;
		delete(pKEPT);
		i++;
	}
	*(value + i) = '\0';
}

void Chislo::Set(char* input) {
	int i = 0;
	temp *pNEW, *pSTART, *pKEPT;

	pNEW = NULL;
	pSTART = NULL;
	pKEPT = NULL;

	while (*(input + i) != '\0') {
		pNEW = new temp;
		pNEW->symb = *(input + i);

		if (pSTART == NULL) {
			pSTART = pNEW;
		}
		else {
			pKEPT->next = pNEW;
		}
		pKEPT = pNEW;

		i++;
	}

	pNEW->next = NULL;

	value = new char[i + 1];

	i = 0;
	pNEW = pSTART;

	while (pNEW != NULL) {
		*(value + i) = pNEW->symb;
		pKEPT = pNEW;
		pNEW = pNEW->next;
		delete(pKEPT);
		i++;
	}
	*(value + i) = '\0';
}

char* Chislo::Get() {
	return value;
}

Chislo::~Chislo() {
	delete(value);
}