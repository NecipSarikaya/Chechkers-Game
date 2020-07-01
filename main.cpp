#include<fstream>
#include<iostream>
#include <string>
#include <sstream>
#include <windows.h>

using namespace std;

int sirakontrol = 1; // Sıra belirlemek için kullanılan global değişken

struct kare { // Her karenin bilgisini tutabilmek için tanımlanan struct yapısı
	int konum;
	string ad;
};


void ekranayaz() {
	ifstream file; // File tanımı
	char text = '\0'; // File dan çekilecek bilginin koyulacağı değişken
	file.open("Game.txt", ios::in);
	if (file) {
		file.seekg(0, ios::beg); //İlk bytedan son bytea kadar okuma yaptıran ve değişkene atayıp bunu yazdıran döngü
		while (!file.eof()) {
			file.get(text);
			cout << text;
		}
	}
	file.close();
}

void yenioyun() {
	fstream fp, fp1; // File tanımı
	char ch; // File dan çekilecek bilginin koyulacağı değişken
	fp.open("NewGame.txt", ios::in);
	if (!fp) {
		cout << "Error While Opening File: " << endl;
	}
	fp1.open("Game.txt", ios::out);
	if (!fp) {
		cout << " Error while Opening file: " << endl;
	}

	while (fp.get(ch)) {  // Kopyalama işlemi
		fp1.put(ch);
	}
	fp.close();
	fp1.close();
}

void ekranaekleme(const char* a, int yer) {
	ofstream file; // File tanımı
	int spot = yer;
	const char* b = a; // File a eklenecek bilginin koyulacağı değişken
	file.open("Game.txt", ios::out | ios::in);
	if (file) {
		file.seekp(spot, ios::beg);
		file.write((char*)b, sizeof(b)); // Belirlenen konuma verilerin işlenmesi
	}
	file.close();
}

bool empty(int konum) {
	int c = konum;
	char text = '\0';
	ifstream file;  // File tanımı
	file.open("Game.txt", ios::in | ios::out);
	if (file) {
		for (int i = c; i < c + 8; i++) { // Konumu verilen karenin boş olup olmadığının kontrolü
			file.seekg(c, ios::beg);
			file.get(text);
			if (text == 'w' || text == 'W' || text == 'b' || text == 'B') {
				return false;
			}
		}
	}
	file.close();
	return true;
}
void sayikontrol(int point[]) {
	int sayib = 0, sayiw = 0;
	char text;
	ifstream file; 
	file.open("Game.txt", ios::in | ios::out);
	if (file) {
		for (int i = 0; i < 64; i++) {
			file.seekg(point[i], ios::beg);
			file.get(text);
			if (text == 'w' || text == 'W' || text == 'WW') { // Beyaz taşların sayısını tutar
				sayiw++;
			}
			else if (text == 'b' || text == 'B' || text == 'BB') { // Siyah taşların sayısını tutar
				sayib++;
			}
		}
		if (sayiw == 1) { //Sona kalan beyaz taşı damaya çevirir
				for (int j = 0; j < 64; j++) {
					file.seekg(point[j], ios::beg);
					file.get(text);
					if (text == 'W') {
						ekranaekleme("WW", point[j]);
					}
				}
		}if (sayib == 1) { //Sona kalan siyah taşı damaya çevirir
				for (int j = 0; j < 64; j++) {
					file.seekg(point[j], ios::beg);
					file.get(text);
					if (text == 'B') {
						ekranaekleme("BB", point[j]);
					}
				}		
		}
		if (sayiw == 0) { //Eğer beyaz taş sayısı 0 olursa oyunu siyahlar kazanmış ilan edilir
			cout << "\nOyunu siyahlar kazandi Tebrikler \n";
			exit(0);
		}if (sayib == 0) { //Eğer siyah taş sayısı 0 olursa oyunu beyazlar kazanmış ilan edilir
			cout << "\nOyunu beyazlar kazandi Tebrikler\n";
			exit(0);
		}
		if (sayiw == 1 && sayib == 1) {
			cout << "\nOyun berabere bitti\n";
			exit(0);
		}
	}
	file.close();
}

void damakontrol(int hamlekonumu) { //Rakibin arkasına sarkarak son karesine ulaşan taşın dama olmasını kontrol eden fonksiyon
	const char* damasiyah = "BB";	// Byte kontrolü yaparak bu işlemi gerçekleştirir
	const char* damabeyaz = "WW";
	int hamlekonum2 = hamlekonumu;
	if (hamlekonum2 == 1 || hamlekonum2 == 10 || hamlekonum2 == 19 || hamlekonum2 == 28 || hamlekonum2 == 37 || hamlekonum2 == 46 || hamlekonum2 == 55 || hamlekonum2 == 64) {
		ekranaekleme(damasiyah, hamlekonum2);
	}
	else if (hamlekonum2 == 1051 || hamlekonum2 == 1060 || hamlekonum2 == 1069 || hamlekonum2 == 1078 || hamlekonum2 == 1087 || hamlekonum2 == 1096 || hamlekonum2 == 1105 || hamlekonum2 == 1114) {
		ekranaekleme(damabeyaz, hamlekonum2);
	}
}
void hamledosya(string hamle, int sirakontrol) { // Hamleleri sequantial acces ile hamleler dosyasına ekler
	char  File2[20] = "hamleler.txt";
	string as = hamle;
	ofstream out_file;
	out_file.open(File2, ios::app);
	if (sirakontrol % 2 == 0) { // Gelişen hamlenin beyazdan mı siyahtan mı olduğunu kontrol eder ve dosyaya hamleyi işler
		out_file << "w: ";
		out_file << as;
		out_file.put('\n');
	}if (sirakontrol % 2 == 1) { // Gelişen hamlenin beyazdan mı siyahtan mı olduğunu kontrol eder ve dosyaya hamleyi işler
		out_file << "b: ";
		out_file << as;
		out_file.put('\n');
	}
	out_file.close();
}
bool tahtakontrol(int sayi) {
	int k, da;
	char ktext = '\0', ktext1, ktext2, ktext3, ktext4,ktext5,ktext6,ktext7;
	ifstream file1;
	int point[64] = { 1,10,19,28,37,46,55,64,151,160,169,178,187,196,205,214,301,310,319,328,337,346,355,364,451,460,469,478,487,496,505,514,601,610,619,628,637,646,655,664,751,760,769,778,787,796,805,814,
	901,910,919,928,937,946,955,964,1051,1060,1069,1078,1087,1096,1105,1114 };  // Her karenin konumunu tutan int array
	file1.open("Game.txt", ios::in);
	if (file1) {
		for (int i = 0; i < 64; i++) {       // Her kareyi kontrol ederek zorunlu hamle kontrol eden döngü
			file1.seekg(point[i], ios::beg);
			file1.get(ktext);					//Kontrol edilen karedeki veriyi tutar
			file1.seekg(point[i] + 1, ios::beg);
			file1.get(ktext5);					// Dama kontrolü için bi sonraki bytedaki veriyi tutar
			file1.seekg(1128, ios::beg);
			file1.get(ktext4);					// Sıranın kimde olduğunu tutar
			k = (int)point[i];
			if (ktext == 'B' && ktext4 == 'B' && ktext5 == 'B') { // ktext değişkeninde karenin içindeki taşın verisi tutulur , ktext4 sıranın kimde olduğunu tutar,ktext5 dama kontrolü için karenin içindeki verinin yanındaki veriyi tutar
				for (int j = 1; j < 8; j++) {
					file1.seekg(k + j * 9, ios::beg);		//Taşın sağ karesindeki taşları gezer ve onları değişkene atar
					file1.get(ktext3);
					if (!(empty(k + j * 9)) && empty(k + j * 9 + 9) && (ktext3 == 'W' || ktext3 == 'WW' )) { //Siyah dama taşının sağında bulunan taşın dolu olup beyaz taş olup olmadığını ve onun sağının boş olup olmadığını kontrol eder
						if (!empty(k + j * 9 - 9)) {  //Yanyana olan iki beyaz taşın zorunlu hamle olmaktan çıkmasını kontrol eder
							break;
						}
						if (k == sayi || k + j * 9 == 64 || k + j * 9 == 214 || k + j * 9 == 364 || k + j * 9 == 514 || k + j * 9 == 664 || k + j * 9 == 814 || k + j * 9 == 964 || k + j * 9 == 1114) {
							return true;	// En sağ sütundaki verileri eleyerek kodun sağlıklı çalışmasını sağlayan kontrol
						}
						cout << "Saga Zorunlu hamle var \n"; // Koşullar sağlanmadığı için zorunlu hamle bildirisi ekrana düşer
						return false;
					}
				}for (int l = 1;l < 8; l++) { 
					if (k - l * 150 < 0) {  // Negatif değelere düşmeyi engelleyen kontrol
						break;
					}
					file1.seekg(k - l * 150, ios::beg); //Taşın üst karesindeki taşları gezer ve onları değişkene atar
					file1.get(ktext1);
					if (!(empty(k - l * 150)) && empty(k - l * 150 - 150) && (ktext1 == 'W' || ktext1 == 'WW')) { //Siyah dama taşının yukarısında bulunan taşın dolu olup beyaz taş olup olmadığını ve onun yukarısının boş olup olmadığını kontrol eder
						if (k == sayi || k-l*150-150 ==1 || k - l * 150-150 == 10 || k - l * 150-150 == 19 || k - l * 150-150 == 28 || k - l * 150-150 == 37 || k - l * 150-150 == 46 || k - l * 150-150 == 55 || k - l * 150-150 == 64 ) {
							return true;		//Üstüste olan iki beyaz taşın zorunlu hamle olmaktan çıkmasını kontrol eder
						}
						cout << "Yukari Zorunlu hamle var \n";// Koşullar sağlanmadığı için zorunlu hamle bildirisi ekrana düşer
						return false;
					}
				}for (int m = 1; m < 8; m++) {
					if (k + m * 150 >1115) {		//Kontrolün tahta içinde kalmasını sağlayan if kontrolü
						break;
					}
					file1.seekg(k + m * 150, ios::beg); //Taşın alt karesindeki taşları gezer ve onları değişkene atar
					file1.get(ktext6);
					if (!(empty(k + m * 150)) && empty(k + m * 150 + 150) && (ktext6 == 'W' || ktext6 == 'WW')) {  //Siyah dama taşının altında bulunan taşın dolu olup beyaz taş olup olmadığını ve onun altının boş olup olmadığını kontrol eder
						if (k == sayi || k + m * 150 + 150 == 1051 || k + m * 150 + 150 == 1060 || k + m * 150 + 150 == 1069 || k + m * 150 + 150 == 1078 || k + m * 150 + 150 == 1087 || k + m * 150 + 150 == 1096 || k + m * 150 + 150 == 1105 || k + m * 150 + 150 == 1144) {
							return true; //Üstüste olan iki beyaz taşın zorunlu hamle olmaktan çıkmasını kontrol eder
						}
						cout << "Asagi Zorunlu hamle var \n";  // Koşullar sağlanmadığı için zorunlu hamle bildirisi ekrana düşer
						return false;
					}
				}for (int n = 1; n < 8; n++) {
					file1.seekg(k - n * 9, ios::beg); //Taşın sol karesindeki taşları gezer ve onları değişkene atar
					file1.get(ktext2);
					if (!(empty(k - n * 9)) && empty(k - n * 9 - 9) && (ktext2 == 'W' || ktext2 == 'WW')) { //Siyah dama taşının solunda bulunan taşın dolu olup beyaz taş olup olmadığını ve onun solunda boş olup olmadığını kontrol eder
						if (!empty(k + n * 9 + 9)) {  // Kodun doğru çalışmasını sağlayan kontrol
							break;
						}
						if (k == sayi || k - n * 9 == 1 || k - n * 9 == 151 || k - n * 9 == 301 || k - n * 9 == 451 || k - n * 9 == 601 || k - n * 9 == 751 || k - n * 9 == 901 || k - n * 9 == 1051) {
							return true; // En sol sütundaki verileri eleyerek kodun sağlıklı çalışmasını sağlayan kontrol
						}
						cout << "Sola Zorunlu hamle var \n";  // Koşullar sağlanmadığı için zorunlu hamle bildirisi ekrana düşer
						return false;
					}
				}
			}
			if (ktext == 'W' && ktext4 == 'W' && ktext5 == 'W') { // ktext değişkeninde karenin içindeki taşın verisi tutulur , ktext4 sıranın kimde olduğunu tutar,ktext5 dama kontrolü için karenin içindeki verinin yanındaki veriyi tutar
				for (int j = 1; j < 8; j++) {
					file1.seekg(k + j * 9, ios::beg); //Taşın sağ karesindeki taşları gezer ve onları değişkene atar
					file1.get(ktext3);
					if (!(empty(k + j * 9)) && empty(k + j * 9 + 9) && (ktext3 == 'B' || ktext3 == 'BB')) {  //Beyaz dama taşının sağında bulunan taşın dolu olup siyah taş olup olmadığını ve onun sağının boş olup olmadığını kontrol eder
						if (!empty(k + j * 9 - 9)) { //Yanyana olan iki siyah taşın zorunlu hamle olmaktan çıkmasını kontrol eder
							break;
						}
						if (k == sayi || k + j * 9 == 64 || k + j * 9 == 214 || k + j * 9 == 364 || k + j * 9 == 514 || k + j * 9 == 664 || k + j * 9 ==814 || k + j * 9 == 964 || k + j * 9 == 1114) {
							return true;   // En sağ sütundaki verileri eleyerek kodun sağlıklı çalışmasını sağlayan kontrol
						}
						cout << "Saga Zorunlu hamle var \n"; // Koşullar sağlanmadığı için zorunlu hamle bildirisi ekrana düşer
						return false;
					}
				}for (int l = 1;l < 8; l++) {
					if (k - l * 150 < 0) { // Negatif değelere düşmeyi engelleyen kontrol
						break;
					}
					file1.seekg(k - l * 150, ios::beg); //Taşın üst karesindeki taşları gezer ve onları değişkene atar
					file1.get(ktext1);
					if (!(empty(k - l * 150)) && empty(k - l * 150 - 150) && (ktext1 == 'B' || ktext1 == 'BB')) {   //Beyaz dama taşının yukarısında bulunan taşın dolu olup siyah taş olup olmadığını ve onun yukarısının boş olup olmadığını kontrol eder
						if (k == sayi || k - l * 150 - 150 == 1 || k - l * 150 - 150 == 10 || k - l * 150 - 150 == 19 || k - l * 150 - 150 == 28 || k - l * 150 - 150 == 37 || k - l * 150 - 150 == 46 || k - l * 150 - 150 == 55 || k - l * 150 - 150 == 64) {
							return true; //Üstüste olan iki siyah taşın zorunlu hamle olmaktan çıkmasını kontrol eder
						}
						cout << "Yukari Zorunlu hamle var \n";  // Koşullar sağlanmadığı için zorunlu hamle bildirisi ekrana düşer
						return false;
					}
				}for (int m = 1; m < 8; m++) {
					if (k + m * 150+150 >1115) { //Kontrolün tahta içinde kalmasını sağlayan if kontrolü
						break;
					}
					file1.seekg(k + m * 150, ios::beg); //Taşın alt karesindeki taşları gezer ve onları değişkene atar
					file1.get(ktext6);
					if (!(empty(k + m * 150)) && empty(k + m * 150 + 150) && (ktext6 == 'B' || ktext6 == 'BB')) { //Beyaz dama taşının altında bulunan taşın dolu olup siyah taş olup olmadığını ve onun altının boş olup olmadığını kontrol eder
						if (k == sayi || k + m * 150 + 150 == 1051 || k + m * 150 + 150 == 1060 || k + m * 150 + 150 == 1069 || k + m * 150 + 150 == 1078 || k + m * 150 + 150 == 1087 || k + m * 150 + 150 == 1096 || k + m * 150 + 150 == 1105 || k + m * 150 + 150 == 1114) {
							return true;  //Üstüste olan iki siyah taşın zorunlu hamle olmaktan çıkmasını kontrol eder
						}
						cout << "Asagi Zorunlu hamle var \n";  // Koşullar sağlanmadığı için zorunlu hamle bildirisi ekrana düşer
						return false;
					}
				}for (int n = 1; n < 8; n++) {
					file1.seekg(k - n * 9, ios::beg); //Taşın sol karesindeki taşları gezer ve onları değişkene atar
					file1.get(ktext2); 
					if (!(empty(k - n * 9)) && empty(k - n * 9 - 9) && (ktext2 == 'B' || ktext2 == 'BB')) {  //Beyaz dama taşının solunda bulunan taşın dolu olup siyah taş olup olmadığını ve onun solunda boş olup olmadığını kontrol eder
						if (!empty(k - n * 9 + 9)) {  // Kodun doğru çalışmasını sağlayan kontrol
							break;
						}
						if (k == sayi || k - n * 9 == 1 || k - n * 9 == 151 || k - n * 9 == 301 || k - n * 9 == 451 || k - n * 9 == 601 || k - n * 9 == 751 || k - n * 9 == 901 || k - n * 9 == 1051) {
							return true; // En sol sütundaki verileri eleyerek kodun sağlıklı çalışmasını sağlayan kontrol
						}
						cout << "Sola Zorunlu hamle var \n"; // Koşullar sağlanmadığı için zorunlu hamle bildirisi ekrana düşer
						return false;
					}
				}
			} 
			if (ktext == 'B' && ktext4 == 'B') { // ktext değişkeninde karenin verisi ktext4 de ise sıranın kimde olduğu tutulur
				file1.seekg(k - 150, ios::beg); // Taşın üstündeki kareyi tutar
				file1.get(ktext1);
				file1.seekg(k - 9, ios::beg);	// Taşın solundaki kareyi tutar
				file1.get(ktext2);
				file1.seekg(k + 9, ios::beg);	//Taşın sağındaki kareyi tutar
				file1.get(ktext3);
				if (!empty(k - 150) && (ktext1 == 'W' || ktext1 == 'WW') && (empty(k - 9) || (!empty(k - 9) && ktext2 == 'B') || (!empty(k - 9) && !empty(k - 18))) && (empty(k + 9) || (!empty(k + 9) && ktext3 == 'B') || (!empty(k + 9) && !empty(k + 18))) && empty(k - 300)) {
					if (k == sayi) {	// Yukarı zorunlu yeme için gerekli kontrol
						return true;
					}
					cout << "Yukari Zorunlu hamle var \n";
					return false;
				}
				else if (!empty(k - 9) && (ktext2 == 'W' || ktext2 == 'WW') && (empty(k - 150) || (!empty(k - 150) && ktext1 == 'B') || (!empty(k - 150) && !empty(k - 300))) && (empty(k + 9) || (!empty(k + 9) && ktext3 == 'B') || (!empty(k + 9) && !empty(k + 18))) && empty(k - 18)) {
					if (k == sayi || (k == 10 || k == 160 || k == 310 || k == 460 || k == 610 || k == 760 || k == 910 || k == 1060)) {		// Sola zorunlu yeme için gerekli kontrol
						return true;	// Sola zorunlu yeme için gerekli kontrol
					}
					cout << "Sola Zorunlu hamle var \n";
					return false;

				}
				else if (!empty(k + 9) && (ktext3 == 'W' || ktext3 == 'WW') && (empty(k - 150) || (!empty(k - 150) && ktext1 == 'B') || (!empty(k - 150) && !empty(k - 300))) && (empty(k - 9) || (!empty(k - 9) && ktext3 == 'B') || (!empty(k - 9) && !empty(k - 18))) && empty(k + 18)) {
					if (k == sayi || k == 55 || k == 205 || k == 355 || k == 505 || k == 655 || k == 805 || k == 955 || k == 1105) {		//Sağa zorunlu yeme için gerekli kontrol
						return true;	// Sağa zorunlu yeme için gerekli kontrol
					}
					cout << "Saga Zorunlu hamle var \n";
					return false;
				}
			}
			else if (ktext == 'W' && ktext4 == 'W') { // ktext değişkeninde karenin verisi ktext4 de ise sıranın kimde olduğu tutulur
				file1.seekg(k + 150, ios::beg); // Taşın altındaki kareyi tutar
				file1.get(ktext1);
				file1.seekg(k - 9, ios::beg);  // Taşın solundaki kareyi tutar
				file1.get(ktext2);
				file1.seekg(k + 9, ios::beg);  //TAşın sağındaki kareyi tutar
				file1.get(ktext3);
				if (!empty(k + 150) && (ktext1 == 'B' || ktext1 == 'BB') && (empty(k - 9) || (!empty(k - 9) && ktext2 == 'W') || (!empty(k - 9) && !empty(k - 18))) && (empty(k + 9) || (!empty(k + 9) && ktext3 == 'W') || (!empty(k + 9) && !empty(k + 18))) && empty(k + 300)) {
					if (k == sayi) {		// Aşağı zorunlu yeme için gerekli kontrol
						return true;
					}
					cout << "Asagi Zorunlu hamle var \n";
					return false;
				}
				else if (!empty(k - 9) && (ktext2 == 'B' || ktext2 == 'BB') && (empty(k + 150) || (!empty(k + 150) && ktext1 == 'W') || (!empty(k + 150) && !empty(k + 300))) && (empty(k + 9) || (!empty(k + 9) && ktext3 == 'W') || (!empty(k + 9) && !empty(k + 18))) && empty(k - 18)) {
					if (k == sayi || (k == 10 || k == 160 || k == 310 || k == 460 || k == 610 || k == 760 || k == 910 || k == 1060)) { 		// Sola zorunlu yeme için gerekli kontrol
						return true;	// Sola zorunlu yeme için gerekli kontrol
					}
					cout << "Sola Zorunlu hamle var \n ";
					return false;

				}
				else if (!empty(k + 9) && (ktext3 == 'B' || ktext3 == 'BB') && (empty(k + 150) || (!empty(k + 150) && ktext1 == 'W') || (!empty(k + 150) && !empty(k + 300))) && (empty(k - 9) || (!empty(k - 9) && ktext3 == 'W') || (!empty(k - 9) && !empty(k - 18))) && empty(k + 18)) {
					if (k == sayi || k == 55 || k == 205 || k == 355 || k == 505 || k == 655 || k == 805 || k == 955 || k == 1105) { 		//Sağa zorunlu yeme için gerekli kontrol
						return true;	// Sağa zorunlu yeme için gerekli kontrol
					}
					cout << "Saga Zorunlu hamle var \n";
					return false;
				}
			}
		}
	}
	file1.close();
	return true;
}

void Oyun(kare a1, kare a2, kare a3, kare a4, kare a5, kare a6, kare a7, kare a8, kare b1, kare b2, kare b3, kare b4, kare b5, kare b6, kare b7, kare b8, kare c1, kare c2, kare c3, kare c4, kare c5, kare c6, kare c7, kare c8, kare d1, kare d2, kare d3, kare d4, kare d5, kare d6, kare d7, kare d8,
	kare e1, kare e2, kare e3, kare e4, kare e5, kare e6, kare e7, kare e8, kare f1, kare f2, kare f3, kare f4, kare f5, kare f6, kare f7, kare f8, kare g1, kare g2, kare g3, kare g4, kare g5, kare g6, kare g7, kare g8, kare h1, kare h2, kare h3, kare h4, kare h5, kare h6, kare h7, kare h8,
	const char* siyah, const char* beyaz, const char* damasiyah, const char* damabeyaz) {
	string hamle = "\0";
	int point[64] = { 1,10,19,28,37,46,55,64,151,160,169,178,187,196,205,214,301,310,319,328,337,346,355,364,451,460,469,478,487,496,505,514,601,610,619,628,637,646,655,664,751,760,769,778,787,796,805,814,
	901,910,919,928,937,946,955,964,1051,1060,1069,1078,1087,1096,1105,1114 };
	int k;
	char ktext = '\0', ktext1, ktext2, ktext3;
	ifstream file1;
	ofstream file;
	while (hamle != "3") {
		Sleep(1000);
		system("cls");		// Ekranı temizleyen fonksiyon
		ekranayaz();
		sayikontrol(point);	//Oyun bitişini hesaplayan fonksiyon
		int hamlekonum1, hamlekonum2;
		x:								// Hata dönen noktalardan oyununun sürekliliğini sağlamak için konulmuş atlama noktası
		cout << "\n Oyundan cikmak icin hamle bolgesine 3 giriniz \n";
		cout << "Hamle giriniz: ";
		cin >> hamle;
		if (hamle == "3") {  // Oyundan çıkış kontrolü
			cout << "IYI GUNlER";
			return;
		}
		if (hamle.length() != 4) {
			cout << " \n Hatali hamle girdiniz  \n";  //Doğru hamle kontrolü
			cin >> hamle;
		}

		string hamleba = hamle.substr(0, 2);  // Hamleyi iki parçaya ayırma
		string hamlebi = hamle.substr(2, 4);

		if (hamleba == a1.ad) {			//Hamlenin hangi kareler arasındaki gerçekleşeceğini kontrol eden if kontrolleri
			hamlekonum1 = a1.konum;
		}
		else if (hamleba == a2.ad) {
			hamlekonum1 = a2.konum;
		}
		else if (hamleba == a3.ad) {
			hamlekonum1 = a3.konum;
		}
		else if (hamleba == a4.ad) {
			hamlekonum1 = a4.konum;
		}
		else if (hamleba == a5.ad) {
			hamlekonum1 = a5.konum;
		}
		else if (hamleba == a6.ad) {
			hamlekonum1 = a6.konum;
		}
		else if (hamleba == a7.ad) {
			hamlekonum1 = a7.konum;
		}
		else if (hamleba == a8.ad) {
			hamlekonum1 = a8.konum;

		}
		else if (hamleba == b1.ad) { 			//Hamlenin hangi kareler arasındaki gerçekleşeceğini kontrol eden if kontrolleri
			hamlekonum1 = b1.konum;
		}
		else if (hamleba == b2.ad) {
			hamlekonum1 = b2.konum;
		}
		else if (hamleba == b3.ad) {
			hamlekonum1 = b3.konum;
		}
		else if (hamleba == b4.ad) {			//Hamlenin hangi kareler arasındaki gerçekleşeceğini kontrol eden if kontrolleri
			hamlekonum1 = b4.konum;
		}
		else if (hamleba == b5.ad) {
			hamlekonum1 = b5.konum;
		}
		else if (hamleba == b6.ad) {
			hamlekonum1 = b6.konum;
		}
		else if (hamleba == b7.ad) {
			hamlekonum1 = b7.konum;
		}
		else if (hamleba == b8.ad) {
			hamlekonum1 = b8.konum;
		}
		else if (hamleba == c1.ad) {
			hamlekonum1 = c1.konum;
		}
		else if (hamleba == c2.ad) {
			hamlekonum1 = c2.konum;
		}
		else if (hamleba == c3.ad) {			//Hamlenin hangi kareler arasındaki gerçekleşeceğini kontrol eden if kontrolleri
			hamlekonum1 = c3.konum;
		}
		else if (hamleba == c4.ad) {
			hamlekonum1 = c4.konum;
		}
		else if (hamleba == c5.ad) {
			hamlekonum1 = c5.konum;
		}
		else if (hamleba == c6.ad) {
			hamlekonum1 = c6.konum;
		}
		else if (hamleba == c7.ad) {
			hamlekonum1 = c7.konum;
		}
		else if (hamleba == c8.ad) {
			hamlekonum1 = c8.konum;
		}
		else if (hamleba == d1.ad) {			//Hamlenin hangi kareler arasındaki gerçekleşeceğini kontrol eden if kontrolleri
			hamlekonum1 = d1.konum;
		}
		else if (hamleba == d2.ad) {
			hamlekonum1 = d2.konum;
		}
		else if (hamleba == d3.ad) {
			hamlekonum1 = d3.konum;
		}
		else if (hamleba == d4.ad) {
			hamlekonum1 = d4.konum;
		}
		else if (hamleba == d5.ad) {
			hamlekonum1 = d5.konum;
		}
		else if (hamleba == d6.ad) {
			hamlekonum1 = d6.konum;
		}
		else if (hamleba == d7.ad) {
			hamlekonum1 = d7.konum;
		}
		else if (hamleba == d8.ad) {
			hamlekonum1 = d8.konum;
		}
		else if (hamleba == e1.ad) {			//Hamlenin hangi kareler arasındaki gerçekleşeceğini kontrol eden if kontrolleri
			hamlekonum1 = e1.konum;
		}
		else if (hamleba == e2.ad) {
			hamlekonum1 = e2.konum;
		}
		else if (hamleba == e3.ad) {
			hamlekonum1 = e3.konum;
		}
		else if (hamleba == e4.ad) {
			hamlekonum1 = e4.konum;
		}
		else if (hamleba == e5.ad) {
			hamlekonum1 = e5.konum;
		}
		else if (hamleba == e6.ad) {
			hamlekonum1 = e6.konum;
		}
		else if (hamleba == e7.ad) {
			hamlekonum1 = e7.konum;
		}
		else if (hamleba == e8.ad) {			//Hamlenin hangi kareler arasındaki gerçekleşeceğini kontrol eden if kontrolleri
			hamlekonum1 = e8.konum;
		}
		else if (hamleba == f1.ad) {
			hamlekonum1 = f1.konum;
		}
		else if (hamleba == f2.ad) {
			hamlekonum1 = f2.konum;
		}
		else if (hamleba == f3.ad) {
			hamlekonum1 = f3.konum;
		}
		else if (hamleba == f4.ad) {
			hamlekonum1 = f4.konum;
		}
		else if (hamleba == f5.ad) {
			hamlekonum1 = f5.konum;
		}
		else if (hamleba == f6.ad) {
			hamlekonum1 = f6.konum;
		}
		else if (hamleba == f7.ad) {			//Hamlenin hangi kareler arasındaki gerçekleşeceğini kontrol eden if kontrolleri
			hamlekonum1 = f7.konum;
		}
		else if (hamleba == f8.ad) {
			hamlekonum1 = f8.konum;
		}
		else if (hamleba == g1.ad) {
			hamlekonum1 = g1.konum;
		}
		else if (hamleba == g2.ad) {
			hamlekonum1 = g2.konum;
		}
		else if (hamleba == g3.ad) {
			hamlekonum1 = g3.konum;
		}
		else if (hamleba == g4.ad) {
			hamlekonum1 = g4.konum;
		}
		else if (hamleba == g5.ad) {			//Hamlenin hangi kareler arasındaki gerçekleşeceğini kontrol eden if kontrolleri
			hamlekonum1 = g5.konum;
		}
		else if (hamleba == g6.ad) {
			hamlekonum1 = g6.konum;
		}
		else if (hamleba == g7.ad) {
			hamlekonum1 = g7.konum;
		}
		else if (hamleba == g8.ad) {
			hamlekonum1 = g8.konum;
		}
		else if (hamleba == h1.ad) {
			hamlekonum1 = h1.konum;
		}
		else if (hamleba == h2.ad) {
			hamlekonum1 = h2.konum;
		}
		else if (hamleba == h3.ad) {
			hamlekonum1 = h3.konum;
		}
		else if (hamleba == h4.ad) {			//Hamlenin hangi kareler arasındaki gerçekleşeceğini kontrol eden if kontrolleri
			hamlekonum1 = h4.konum;
		}
		else if (hamleba == h5.ad) {
			hamlekonum1 = h5.konum;
		}
		else if (hamleba == h6.ad) {
			hamlekonum1 = h6.konum;
		}
		else if (hamleba == h7.ad) {
			hamlekonum1 = h7.konum;
		}
		else if (hamleba == h8.ad) {
			hamlekonum1 = h8.konum;
		}
		else {
		cout << " \n Hatali hamle girdiniz  \n";
		}
		if (hamlebi == a1.ad) {
			hamlekonum2 = a1.konum;
		}
		else if (hamlebi == a2.ad) {			//Hamlenin hangi kareler arasındaki gerçekleşeceğini kontrol eden if kontrolleri
			hamlekonum2 = a2.konum;
		}
		else if (hamlebi == a3.ad) {
			hamlekonum2 = a3.konum;
		}
		else if (hamlebi == a4.ad) {
			hamlekonum2 = a4.konum;
		}
		else if (hamlebi == a5.ad) {
			hamlekonum2 = a5.konum;
		}
		else if (hamlebi == a6.ad) {
			hamlekonum2 = a6.konum;
		}
		else if (hamlebi == a7.ad) {
			hamlekonum2 = a7.konum;
		}
		else if (hamlebi == a8.ad) {			//Hamlenin hangi kareler arasındaki gerçekleşeceğini kontrol eden if kontrolleri
			hamlekonum2 = a8.konum;

		}
		else if (hamlebi == b1.ad) {
			hamlekonum2 = b1.konum;
		}
		else if (hamlebi == b2.ad) {
			hamlekonum2 = b2.konum;
		}
		else if (hamlebi == b3.ad) {
			hamlekonum2 = b3.konum;
		}
		else if (hamlebi == b4.ad) {
			hamlekonum2 = b4.konum;
		}
		else if (hamlebi == b5.ad) {
			hamlekonum2 = b5.konum;
		}
		else if (hamlebi == b6.ad) {
			hamlekonum2 = b6.konum;
		}
		else if (hamlebi == b7.ad) {			//Hamlenin hangi kareler arasındaki gerçekleşeceğini kontrol eden if kontrolleri
			hamlekonum2 = b7.konum;
		}
		else if (hamlebi == b8.ad) {
			hamlekonum2 = b8.konum;
		}
		else if (hamlebi == c1.ad) {
			hamlekonum2 = c1.konum;
		}
		else if (hamlebi == c2.ad) {
			hamlekonum2 = c2.konum;
		}
		else if (hamlebi == c3.ad) {
			hamlekonum2 = c3.konum;
		}
		else if (hamlebi == c4.ad) {
			hamlekonum2 = c4.konum;
		}
		else if (hamlebi == c5.ad) {			//Hamlenin hangi kareler arasındaki gerçekleşeceğini kontrol eden if kontrolleri
			hamlekonum2 = c5.konum;
		}
		else if (hamlebi == c6.ad) {
			hamlekonum2 = c6.konum;
		}
		else if (hamlebi == c7.ad) {
			hamlekonum2 = c7.konum;
		}
		else if (hamlebi == c8.ad) {
			hamlekonum2 = c8.konum;
		}
		else if (hamlebi == d1.ad) {
			hamlekonum2 = d1.konum;
		}
		else if (hamlebi == d2.ad) {
			hamlekonum2 = d2.konum;
		}
		else if (hamlebi == d3.ad) {
			hamlekonum2 = d3.konum;
		}
		else if (hamlebi == d4.ad) {
			hamlekonum2 = d4.konum;
		}
		else if (hamlebi == d5.ad) {			//Hamlenin hangi kareler arasındaki gerçekleşeceğini kontrol eden if kontrolleri
			hamlekonum2 = d5.konum;
		}
		else if (hamlebi == d6.ad) {
			hamlekonum2 = d6.konum;
		}
		else if (hamlebi == d7.ad) {
			hamlekonum2 = d7.konum;
		}
		else if (hamlebi == d8.ad) {
			hamlekonum2 = d8.konum;
		}
		else if (hamlebi == e1.ad) {
			hamlekonum2 = e1.konum;
		}
		else if (hamlebi == e2.ad) {
			hamlekonum2 = e2.konum;
		}
		else if (hamlebi == e3.ad) {
			hamlekonum2 = e3.konum;
		}
		else if (hamlebi == e4.ad) {			//Hamlenin hangi kareler arasındaki gerçekleşeceğini kontrol eden if kontrolleri
			hamlekonum2 = e4.konum;
		}
		else if (hamlebi == e5.ad) {
			hamlekonum2 = e5.konum;
		}
		else if (hamlebi == e6.ad) {
			hamlekonum2 = e6.konum;
		}
		else if (hamlebi == e7.ad) {
			hamlekonum2 = e7.konum;
		}
		else if (hamlebi == e8.ad) {
			hamlekonum2 = e8.konum;
		}
		else if (hamlebi == f1.ad) {
			hamlekonum2 = f1.konum;
		}
		else if (hamlebi == f2.ad) {
			hamlekonum2 = f2.konum;
		}
		else if (hamlebi == f3.ad) {			//Hamlenin hangi kareler arasındaki gerçekleşeceğini kontrol eden if kontrolleri
			hamlekonum2 = f3.konum;
		}
		else if (hamlebi == f4.ad) {
			hamlekonum2 = f4.konum;
		}
		else if (hamlebi == f5.ad) {
			hamlekonum2 = f5.konum;
		}
		else if (hamlebi == f6.ad) {
			hamlekonum2 = f6.konum;
		}
		else if (hamlebi == f7.ad) {
			hamlekonum2 = f7.konum;
		}
		else if (hamlebi == f8.ad) {
			hamlekonum2 = f8.konum;
		}
		else if (hamlebi == g1.ad) {
			hamlekonum2 = g1.konum;
		}
		else if (hamlebi == g2.ad) {			//Hamlenin hangi kareler arasındaki gerçekleşeceğini kontrol eden if kontrolleri
			hamlekonum2 = g2.konum;
		}
		else if (hamlebi == g3.ad) {
			hamlekonum2 = g3.konum;
		}
		else if (hamlebi == g4.ad) {
			hamlekonum2 = g4.konum;
		}
		else if (hamlebi == g5.ad) {
			hamlekonum2 = g5.konum;
		}
		else if (hamlebi == g6.ad) {
			hamlekonum2 = g6.konum;
		}
		else if (hamlebi == g7.ad) {
			hamlekonum2 = g7.konum;
		}
		else if (hamlebi == g8.ad) {
			hamlekonum2 = g8.konum;
		}
		else if (hamlebi == h1.ad) {			//Hamlenin hangi kareler arasındaki gerçekleşeceğini kontrol eden if kontrolleri
			hamlekonum2 = h1.konum;
		}
		else if (hamlebi == h2.ad) {
			hamlekonum2 = h2.konum;
		}
		else if (hamlebi == h3.ad) {
			hamlekonum2 = h3.konum;
		}
		else if (hamlebi == h4.ad) {
			hamlekonum2 = h4.konum;
		}
		else if (hamlebi == h5.ad) {
			hamlekonum2 = h5.konum;
		}
		else if (hamlebi == h6.ad) {
			hamlekonum2 = h6.konum;
		}
		else if (hamlebi == h7.ad) {			//Hamlenin hangi kareler arasındaki gerçekleşeceğini kontrol eden if kontrolleri
			hamlekonum2 = h7.konum;
		}
		else if (hamlebi == h8.ad) {
			hamlekonum2 = h8.konum;
		}
		else {
		cout << " \n Hatali hamle girdiniz  \n";
		}

		cout << "\n Hamle: " << hamle <<"\n";

		// string hamleba hamlekonum1 hamlebi hamlekonum2

		int hamle1kontrol, hamle2kontrol;
		istringstream(hamleba.substr(1, 1)) >> hamle1kontrol;  //Hamlenin doğruluğunu kontrol etmek için ayrıştırma
		istringstream(hamlebi.substr(1, 1)) >> hamle2kontrol;
		if (!tahtakontrol(hamlekonum1)) {  //Zorunlu hamlelerin kontrolünün yapıldığı if kontrolü
			ekranayaz();
			cout << "\n";
			goto x;
		}
		char kontrol1,sira;
		file1.open("Game.txt", ios::in | ios::out);
		if (file1) {
			file1.seekg(hamlekonum1, ios::beg);
			file1.get(kontrol1); // Hamle başlatılan noktadaki dama taşını kontrol eder
			file1.seekg(1128, ios::beg);
			file1.get(sira);
		}
		file1.close();
		if (sira == 'B') {		//Oyuna devam edildiği takdirde sıra kontrolünün düzgün çalışmasını sağlamak için if kontrolü
			sirakontrol = 0;
		}
		int damas, aa, xx = 0,damak,yy=0;
		char dama1, dama2, dama3, dama4;
		file1.open("Game.txt", ios::in | ios::out);
		if (file1) {
			for (int i = 0; i < 64; i++) {
				file1.seekg(point[i], ios::beg);	
				file1.get(dama1);
				file1.seekg(1128, ios::beg);
				file1.get(dama4);
				file1.seekg(point[i] + 1, ios::beg);
				file1.get(dama2);
				if (dama1 == 'W' && dama2 == 'W') {		//Dama taşı kontrolü

					if (hamlekonum1 == point[i] && empty(hamlekonum2)) {  //Doğru dama taşının hareket ettğinin kontrolü

						if (hamlekonum2 - hamlekonum1 >= 150 && hamleba.substr(0, 1) == hamlebi.substr(0, 1) && dama4 == 'W') { // Dama taşının aynı sutün içindeki aşağı hareketi
							damas = hamlekonum2 - hamlekonum1;
							damas = damas / 150;		//Kontrol için kaç kare gidileceğini tutan değişken
							for (int j = 1; j < damas + 1; j++) {	//Kontrol edilicek karelerin kontrolü için döngü
								aa = point[i] + j * 150;	//Bir alttaki karenin konuunu tutan değişken
								file1.seekg(aa, ios::beg);
								file1.get(dama3);
								damak = (hamlekonum2 - aa)/150;		//İki taş üstünden atlamayı engellemek için gidilebilecek kareler içinde kontrol için gerekli değişken
									if (!empty(aa) && dama3 == 'B' && empty(aa + 150)) {	// Gidilebilecek karelerden dolu olup içinde beyaz taş bulunan bir taşın yenilebilip yenilemeyeceğinin kontrolü
										for (int k = 0; k < damak; k++) {
											if (!empty(hamlekonum2 - k * 150)) {  //İki taş üstünden atlamayı engellemek için gerekli kontrol
												cout << " \n Hatali hamle girdiniz  \n";
												ekranayaz();
												goto x;
											}
										}
										ekranaekleme("\0", hamlekonum1); //Yeme işlemi
										ekranaekleme("\0", aa);
										ekranaekleme(damabeyaz, hamlekonum2);
										hamledosya(hamle, sirakontrol);
										xx++;
									}
									if (!empty(aa) && xx == 0) { //Yeme işlemi olmadıysa ve yenicek taş varken başka nokta girildiyse hata verir
										xx = 0;
										cout << " \n Hatali hamle girdiniz  \n";
										goto x;
									}
									
								}	
							if (xx == 0) {		//Dama taşının taş yemeden normal hareketi 
								ekranaekleme("\0", hamlekonum1);
								ekranaekleme(damabeyaz, hamlekonum2);
								sirakontrol++;
							}
						}

						if (hamlekonum1 - hamlekonum2 >= 150 && hamleba.substr(0, 1) == hamlebi.substr(0, 1) && dama4 == 'W') { // Dama taşının aynı sutün içindeki aşağı hareketi
							damas = hamlekonum1 - hamlekonum2;
							damas = damas / 150;					//Kontrol için kaç kare gidileceğini tutan değişken
							for (int j = 1; j < damas + 1; j++) {	//Kontrol edilicek karelerin kontrolü için döngü
								aa = point[i] - j * 150;		//Bir üstteki karenin konuunu tutan değişken
								file1.seekg(aa, ios::beg);
								file1.get(dama3);
								damak = (aa-hamlekonum2) / 150;		//İki taş üstünden atlamayı engellemek için gidilebilecek kareler içinde kontrol için gerekli değişken
								if (!empty(aa) && dama3 == 'B' && empty(aa - 150)) { // Gidilebilecek karelerden dolu olup içinde beyaz taş bulunan bir taşın yenilebilip yenilemeyeceğinin kontrolü
									for (int k = 0; k < damak; k++) {
										if (!empty(hamlekonum2 + k * 150)) {	//İki taş üstünden atlamayı engellemek için gerekli kontrol
											cout << " \n Hatali hamle girdiniz  \n";
											ekranayaz();
											goto x;
										}
									}
									ekranaekleme("\0", hamlekonum1);	//Yeme işlemi
									ekranaekleme("\0", aa);
									ekranaekleme(damabeyaz, hamlekonum2);
									hamledosya(hamle, sirakontrol);
									xx++;
								}
								if (!empty(aa) && xx == 0) {	 //Yeme işlemi olmadıysa ve yenicek taş varken başka nokta girildiyse hata verir
									xx = 0;
									cout << " \n Hatali hamle girdiniz  \n";
									goto x;
								}
							}
							if (xx == 0) {		//Dama taşının taş yemeden normal hareketi 
								ekranaekleme("\0", hamlekonum1);
								ekranaekleme(damabeyaz, hamlekonum2);
								sirakontrol++;
							}
						}

						if (hamlekonum2 - hamlekonum1 >= 9 && hamlekonum2 - hamlekonum1 < 100 && hamleba.substr(0, 1) != hamlebi.substr(0, 1) && dama4 == 'W') { // Dama taşının aynı satır içindeki sağa hareketi
							damas = hamlekonum2 - hamlekonum1;
							damas = damas / 9;					//Kontrol için kaç kare gidileceğini tutan değişken
							for (int j = 1; j < damas + 1; j++) {	//Kontrol edilicek karelerin kontrolü için döngü
								aa = point[i] + j * 9;			//Bir sağındaki karenin konuunu tutan değişken
								file1.seekg(aa, ios::beg);
								file1.get(dama3);
								damak = (hamlekonum2 - aa) / 9;		//İki taş üstünden atlamayı engellemek için gidilebilecek kareler içinde kontrol için gerekli değişken
								if (!empty(aa) && dama3 == 'B' && empty(aa + 9)) { // Gidilebilecek karelerden dolu olup içinde beyaz taş bulunan bir taşın yenilebilip yenilemeyeceğinin kontrolü
									for (int k = 0; k < damak; k++) {
										if (!empty(hamlekonum2 - k * 9)) { //İki taş üstünden atlamayı engellemek için gerekli kontrol
											cout << " \n Hatali hamle girdiniz  \n";
											ekranayaz();
											goto x;
										}
									} 
									ekranaekleme("\0", hamlekonum1); //Yeme işlemi
									ekranaekleme("\0", aa);
									ekranaekleme(damabeyaz, hamlekonum2);
									hamledosya(hamle, sirakontrol);
									xx++;
								}
								if (!empty(aa) && xx == 0) {  //Yeme işlemi olmadıysa ve yenicek taş varken başka nokta girildiyse hata verir
									xx = 0;
									cout << " \n Hatali hamle girdiniz  \n";
									goto x;
								}
							}
							if (xx == 0) { //Dama taşının taş yemeden normal hareketi 
								ekranaekleme("\0", hamlekonum1);
								ekranaekleme(damabeyaz, hamlekonum2);
								sirakontrol++;
							}
						}
						if (hamlekonum1 - hamlekonum2 >= 9 && hamlekonum1 - hamlekonum2 < 100 && hamleba.substr(0, 1) != hamlebi.substr(0, 1) && dama4 == 'W') { // Dama taşının aynı satır içindeki sola hareketi
							damas = hamlekonum1 - hamlekonum2;
							damas = damas / 9;					//Kontrol için kaç kare gidileceğini tutan değişken
							for (int j = 1; j < damas + 1; j++) {	//Kontrol edilicek karelerin kontrolü için döngü
								aa = point[i] - j * 9;			//Bir solundaki karenin konuunu tutan değişken
								file1.seekg(aa, ios::beg);
								file1.get(dama3);
								damak = (aa - hamlekonum2) / 9;		//İki taş üstünden atlamayı engellemek için gidilebilecek kareler içinde kontrol için gerekli değişken
								if (!empty(aa) && dama3 == 'B' && empty(aa - 9)) {	 // Gidilebilecek karelerden dolu olup içinde beyaz taş bulunan bir taşın yenilebilip yenilemeyeceğinin kontrolü
									for (int k = 0; k < damak; k++) {
										if (!empty(hamlekonum2 + k * 9)) {	//İki taş üstünden atlamayı engellemek için gerekli kontrol
											cout << " \n Hatali hamle girdiniz  \n";
											ekranayaz();
											goto x;
										}
									}
									ekranaekleme("\0", hamlekonum1);	//Yeme işlemi
									ekranaekleme("\0", aa);
									ekranaekleme(damabeyaz, hamlekonum2);
									hamledosya(hamle, sirakontrol);
									xx++;
								}
								if (!empty(aa) && xx == 0) {  //Yeme işlemi olmadıysa ve yenicek taş varken başka nokta girildiyse hata verir
									xx = 0;
									cout << " \n Hatali hamle girdiniz  \n";
									goto x;
								}
							}
							if (xx == 0) {		//Dama taşının taş yemeden normal hareketi 
								ekranaekleme("\0", hamlekonum1);
								ekranaekleme(damabeyaz, hamlekonum2);
								sirakontrol++;
							}
						}

					}
				}
				if (dama1 == 'B' && dama2 == 'B') {			//Dama taşı kontrolü
					if (hamlekonum1 == point[i] && empty(hamlekonum2)) {		 //Doğru dama taşının hareket ettğinin kontrolü
						if (hamlekonum2 - hamlekonum1 >= 150 && hamleba.substr(0, 1) == hamlebi.substr(0, 1) && dama4 == 'B') {  // Dama taşının aynı sütun içindeki aşağı hareketi
							damas = hamlekonum2 - hamlekonum1;
							damas = damas / 150;					//Kontrol için kaç kare gidileceğini tutan değişken
							for (int j = 1; j < damas + 1; j++) {	//Kontrol edilicek karelerin kontrolü için döngü
								aa = point[i] + j * 150;			//Bir altındaki karenin konuunu tutan değişken
								file1.seekg(aa, ios::beg);
								file1.get(dama3);
								damak = (hamlekonum2-aa) / 150;	//İki taş üstünden atlamayı engellemek için gidilebilecek kareler içinde kontrol için gerekli değişken
								if (!empty(aa) && dama3 == 'W' && empty(aa + 150)) {	 // Gidilebilecek karelerden dolu olup içinde beyaz taş bulunan bir taşın yenilebilip yenilemeyeceğinin kontrolü
									for (int k = 0; k < damak; k++) {
										if (!empty(hamlekonum2 - k * 150)) {	//İki taş üstünden atlamayı engellemek için gerekli kontrol
											cout << " \n Hatali hamle girdiniz  \n";
											ekranayaz();
											goto x;
										}
									}
									ekranaekleme("\0", hamlekonum1); //Yeme işlemi
									ekranaekleme("\0", aa);
									ekranaekleme(damasiyah, hamlekonum2);
									hamledosya(hamle, sirakontrol);
									xx++;
								}
								if (!empty(aa) && xx == 0) {	//Yeme işlemi olmadıysa ve yenicek taş varken başka nokta girildiyse hata verir
									xx = 0;
									cout << " \n Hatali hamle girdiniz  \n";
									goto x;
								}
							}
							if (xx == 0) {	//Dama taşının taş yemeden normal hareketi 
								ekranaekleme("\0", hamlekonum1);
								ekranaekleme(damasiyah, hamlekonum2);
								sirakontrol++;
							}
						}

						if (hamlekonum1 - hamlekonum2 >= 150 && hamleba.substr(0, 1) == hamlebi.substr(0, 1) && dama4 == 'B') {	// Dama taşının aynı sütun içindeki yukarı hareketi
							damas = hamlekonum1 - hamlekonum2;
							damas = damas / 150;				//Kontrol için kaç kare gidileceğini tutan değişken
							for (int j = 1; j < damas + 1; j++) {	//Kontrol edilicek karelerin kontrolü için döngü
								aa = point[i] - j * 150;			//Bir altındaki karenin konuunu tutan değişken
								file1.seekg(aa, ios::beg);
								file1.get(dama3);
								damak = (aa - hamlekonum2) / 150;		//İki taş üstünden atlamayı engellemek için gidilebilecek kareler içinde kontrol için gerekli değişken
								if (!empty(aa) && dama3 == 'W' && empty(aa - 150)) {	 // Gidilebilecek karelerden dolu olup içinde beyaz taş bulunan bir taşın yenilebilip yenilemeyeceğinin kontrolü
									for (int k = 0; k < damak; k++) {
										if (!empty(hamlekonum2 + k * 150)) {	//İki taş üstünden atlamayı engellemek için gerekli kontrol
											cout << " \n Hatali hamle girdiniz  \n";
											ekranayaz();
											goto x;
										}
									}
									ekranaekleme("\0", hamlekonum1);	 //Yeme işlemi
									ekranaekleme("\0", aa);
									ekranaekleme(damasiyah, hamlekonum2);
									hamledosya(hamle, sirakontrol);
									xx++;
								}
								if (!empty(aa) && xx == 0) {	//Yeme işlemi olmadıysa ve yenicek taş varken başka nokta girildiyse hata verir
									xx = 0;
									cout << " \n Hatali hamle girdiniz  \n";
									goto x;
								}
							}
							if (xx == 0) {	//Dama taşının taş yemeden normal hareketi 
								ekranaekleme("\0", hamlekonum1);
								ekranaekleme(damasiyah, hamlekonum2);
								sirakontrol++;
							}
						}
						if (hamlekonum2 - hamlekonum1 >= 9 && hamlekonum2 - hamlekonum1 < 100 && hamleba.substr(0, 1) != hamlebi.substr(0, 1) && dama4 == 'B') {
							damas = hamlekonum2 - hamlekonum1;
							damas = damas / 9;					//Kontrol için kaç kare gidileceğini tutan değişken
							for (int j = 1; j < damas + 1; j++) {	//Kontrol edilicek karelerin kontrolü için döngü
								aa = point[i] + j * 9;			//Bir sağındaki karenin konuunu tutan değişken
								file1.seekg(aa, ios::beg);
								file1.get(dama3);
								damak = (hamlekonum2-aa) / 9;		//İki taş üstünden atlamayı engellemek için gidilebilecek kareler içinde kontrol için gerekli değişken
								if (!empty(aa) && dama3 == 'W' && empty(aa + 9)) {	// Gidilebilecek karelerden dolu olup içinde beyaz taş bulunan bir taşın yenilebilip yenilemeyeceğinin kontrolü
									for (int k = 0; k < damak; k++) {
										if (!empty(hamlekonum2 - k * 9)) { //İki taş üstünden atlamayı engellemek için gerekli kontrol
											cout << " \n Hatali hamle girdiniz  \n";
											ekranayaz();
											goto x;
										}
									}	
									ekranaekleme("\0", hamlekonum1);	 //Yeme işlemi
									ekranaekleme("\0", aa);
									ekranaekleme(damasiyah, hamlekonum2);
									hamledosya(hamle, sirakontrol);
									xx++;
								}
								if (!empty(aa) && xx == 0) {	//Yeme işlemi olmadıysa ve yenicek taş varken başka nokta girildiyse hata verir
									xx = 0;
									cout << " \n Hatali hamle girdiniz1  \n";
									goto x;
								}
							}
							if (xx == 0) {	//Dama taşının taş yemeden normal hareketi 
								ekranaekleme("\0", hamlekonum1);
								ekranaekleme(damasiyah, hamlekonum2);
								sirakontrol++;
							}
						}
						if (hamlekonum1 - hamlekonum2 >= 9 && hamlekonum1 - hamlekonum2 < 100 && hamleba.substr(0, 1) != hamlebi.substr(0, 1) && dama4 == 'B') {
							damas = hamlekonum1 - hamlekonum2;
							damas = damas / 9;					//Kontrol için kaç kare gidileceğini tutan değişken
							for (int j = 1; j < damas + 1; j++) {	//Kontrol edilicek karelerin kontrolü için döngü
								aa = point[i] - j * 9;			//Bir solundaki karenin konuunu tutan değişken
								file1.seekg(aa, ios::beg);
								file1.get(dama3);
								damak = (aa - hamlekonum2) / 9;		//İki taş üstünden atlamayı engellemek için gidilebilecek kareler içinde kontrol için gerekli değişken
								if (!empty(aa) && dama3 == 'W' && empty(aa - 9)) {	// Gidilebilecek karelerden dolu olup içinde beyaz taş bulunan bir taşın yenilebilip yenilemeyeceğinin kontrolü
									for (int k = 0; k < damak; k++) {
										if (!empty(hamlekonum2 + k * 9)) {	//İki taş üstünden atlamayı engellemek için gerekli kontrol
											cout << " \n Hatali hamle girdiniz  \n";
											ekranayaz();
											goto x;
										}
									}
									ekranaekleme("\0", hamlekonum1);	 //Yeme işlemi
									ekranaekleme("\0", aa);
									ekranaekleme(damasiyah, hamlekonum2);
									hamledosya(hamle, sirakontrol);
									xx++;
								}
								if (!empty(aa) && xx == 0) {	//Yeme işlemi olmadıysa ve yenicek taş varken başka nokta girildiyse hata verir
									xx = 0;
									cout << " \n Hatali hamle girdiniz  \n";
									goto x;
								}
							}
							if (xx == 0) {	//Dama taşının taş yemeden normal hareketi 
								ekranaekleme("\0", hamlekonum1);
								ekranaekleme(damasiyah, hamlekonum2);
								sirakontrol++;
							}
						}
					}
				}
			}
		}
		file1.close();
		char ktext4;
		int gecti = 0;
		file1.open("Game.txt", ios::in);
		if (file1) {
			file1.seekg(hamlekonum1, ios::beg);
			file1.get(ktext);
			file1.seekg(1128, ios::beg);
			file1.get(ktext4);
			if (ktext == 'B' && ktext4 == 'B') { //Taşın siyah olup olmadığının kontrolü ve sıranın siyahta olduğunun kontrolü
				k = hamlekonum1;
				file1.seekg(k - 150, ios::beg);	//Taşın üstündeki kareyi tutan değişken
				file1.get(ktext1);
				file1.seekg(k - 9, ios::beg);	//Taşın solundaki kareyi tutan değişken
				file1.get(ktext2);
				file1.seekg(k + 9, ios::beg);	//Taşın sağındaki kareyi tutan değişken
				file1.get(ktext3);
				if (!empty(k - 150) && ktext1 == 'W' && (empty(k - 9) || (!empty(k - 9) && ktext2 == 'B') || (!empty(k - 9) && !empty(k - 18))) && (empty(k + 9) || (!empty(k + 9) && ktext2 == 'B') || (!empty(k + 9) && !empty(k + 18))) && empty(k - 300)) {
					ekranaekleme("\0", hamlekonum1);	//Siyah taş için yukarı yeme kontrolü
					ekranaekleme("\0", hamlekonum1 - 150);
					ekranaekleme(siyah, hamlekonum2);
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}
				else if (!empty(k - 9) && ktext2 == 'W' && (empty(k - 150) || (!empty(k - 150) && ktext2 == 'B') || (!empty(k - 150) && !empty(k - 300))) && (empty(k + 9) || (!empty(k + 9) && ktext2 == 'B') || (!empty(k + 9) && !empty(k + 18))) && empty(k - 18)) {
					ekranaekleme("\0", hamlekonum1);	//Siyah taş için sola yeme kontrolü
					ekranaekleme("\0", hamlekonum1 - 9);
					ekranaekleme(siyah, hamlekonum2);
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}
				else if (!empty(k + 9) && ktext3 == 'W' && (empty(k - 150) || (!empty(k - 150) && ktext2 == 'B') || (!empty(k - 150) && !empty(k - 300))) && (empty(k - 9) || (!empty(k - 9) && ktext2 == 'B') || (!empty(k - 9) && !empty(k - 18))) && empty(k + 18)) {
					ekranaekleme("\0", hamlekonum1);	//Siyah taş için sağa yeme kontrolü
					ekranaekleme("\0", hamlekonum1 + 9);
					ekranaekleme(siyah, hamlekonum2);
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}
			}if (ktext == 'W' && ktext4 == 'W') {	//Taşın beyaz olup olmadığının kontrolü ve sıranın beyazda olduğunun kontrolü
				k = hamlekonum1;
				file1.seekg(k + 150, ios::beg);	//Taşın altındaki kareyi tutan değişken
				file1.get(ktext1);
				file1.seekg(k - 9, ios::beg);	//Taşın solundaki kareyi tutan değişken
				file1.get(ktext2);
				file1.seekg(k + 9, ios::beg);	//Taşın sağındaki kareyi tutan değişken
				file1.get(ktext3);
				if (!empty(k + 150) && ktext1 == 'B' && (empty(k - 9) || (!empty(k - 9) && ktext2 == 'W') || (!empty(k - 9) && !empty(k - 18))) && (empty(k + 9) || (!empty(k + 9) && ktext2 == 'W') || (!empty(k + 9) && !empty(k + 18))) && empty(k + 300)) {
					ekranaekleme("\0", hamlekonum1);	//Beyaz taş için aşağı yeme kontrolü
					ekranaekleme("\0", hamlekonum1 + 150);
					ekranaekleme(beyaz, hamlekonum2);
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}
				else if (!empty(k - 9) && ktext2 == 'B' && (empty(k + 150) || (!empty(k + 150) && ktext2 == 'W') || (!empty(k + 150) && !empty(k + 300))) && (empty(k + 9) || (!empty(k + 9) && ktext2 == 'W') || (!empty(k + 9) && !empty(k + 18))) && empty(k - 18)) {
					ekranaekleme("\0", hamlekonum1);	//Beyaz taş için sola yeme kontrolü
					ekranaekleme("\0", hamlekonum1 - 9);
					ekranaekleme(beyaz, hamlekonum2);
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}
				else if (!empty(k + 9) && ktext3 == 'B' && (empty(k + 150) || (!empty(k + 150) && ktext2 == 'W') || (!empty(k + 150) && !empty(k + 300))) && (empty(k - 9) || (!empty(k - 9) && ktext2 == 'W') || (!empty(k - 9) && !empty(k - 18))) && empty(k + 18)) {
					ekranaekleme("\0", hamlekonum1);	//Beyaz taş için sağa yeme kontrolü
					ekranaekleme("\0", hamlekonum1 + 9);
					ekranaekleme(beyaz, hamlekonum2);
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}
			}
		}
		file1.close();
		if (empty(hamlekonum2) && (!empty(hamlekonum1))) { //Taşların normal hareketinin kontrolü
			if (kontrol1 == 'B' && ktext4 == 'B') {		// Taşın siyah olup olmadığının kontrolü
				if (hamleba.substr(0, 1) == "a" && hamlebi.substr(0, 1) == "a" && hamle2kontrol - hamle1kontrol == 1) { // Siyah taşın a  sütununda yukarı hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(siyah, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}if (hamleba.substr(0, 1) == "a" && hamlebi.substr(0, 1) == "b" && hamle2kontrol - hamle1kontrol == 0) {// Siyah taşın a  sütunundan b sütununa hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(siyah, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}
				if (hamleba.substr(0, 1) == "a" && (hamlebi.substr(0, 1) != "b" || hamlebi.substr(0, 1) != "a") && !(hamle2kontrol - hamle1kontrol == 1 || hamle2kontrol - hamle1kontrol == 0)) {
					cout << " \n Hatali hamle girdiniz  \n";	//Hatalı hamle kontrolü
				}
				if (hamleba.substr(0, 1) == "b" && (hamlebi.substr(0, 1) == "a" || hamlebi.substr(0, 1) == "c") && hamle2kontrol - hamle1kontrol == 0) {// Siyah taşın b  sütunundan a ve c sütunlarına hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(siyah, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}if (hamleba.substr(0, 1) == "b" && hamlebi.substr(0, 1) == "b" && hamle2kontrol - hamle1kontrol == 1) { // Siyah taşın b  sütununda yukarı hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(siyah, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}
				if (hamleba.substr(0, 1) == "b" && (hamlebi.substr(0, 1) != "b" || hamlebi.substr(0, 1) != "a" || hamlebi.substr(0, 1) != "c") && !(hamle2kontrol - hamle1kontrol == 1 || hamle2kontrol - hamle1kontrol == 0)) {
					cout << " \n Hatali hamle girdiniz  \n";	//Hatalı hamle kontrolü
				}
				if (hamleba.substr(0, 1) == "c" && (hamlebi.substr(0, 1) == "b" || hamlebi.substr(0, 1) == "d") && hamle2kontrol - hamle1kontrol == 0) {	// Siyah taşın c  sütunundan b ve d sütunlarına hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(siyah, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}if (hamleba.substr(0, 1) == "c" && hamlebi.substr(0, 1) == "c" && hamle2kontrol - hamle1kontrol == 1) {	// Siyah taşın c  sütununda yukarı hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(siyah, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}
				if (hamleba.substr(0, 1) == "c" && (hamlebi.substr(0, 1) != "b" || hamlebi.substr(0, 1) != "d" || hamlebi.substr(0, 1) != "c") && !(hamle2kontrol - hamle1kontrol == 1 || hamle2kontrol - hamle1kontrol == 0)) {
					cout << " \n Hatali hamle girdiniz  \n";	//Hatalı hamle kontrolü
				}
				if (hamleba.substr(0, 1) == "d" && (hamlebi.substr(0, 1) == "c" || hamlebi.substr(0, 1) == "e") && hamle2kontrol - hamle1kontrol == 0) {	// Siyah taşın d  sütunundan c ve e sütunlarına hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(siyah, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}if (hamleba.substr(0, 1) == "d" && hamlebi.substr(0, 1) == "d" && hamle2kontrol - hamle1kontrol == 1) {	// Siyah taşın d  sütununda yukarı hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(siyah, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}
				if (hamleba.substr(0, 1) == "d" && (hamlebi.substr(0, 1) != "d" || hamlebi.substr(0, 1) != "e" || hamlebi.substr(0, 1) != "c") && !(hamle2kontrol - hamle1kontrol == 1 || hamle2kontrol - hamle1kontrol == 0)) {
					cout << " \n Hatali hamle girdiniz  \n";	//Hatalı hamle kontrolü
				}
				if (hamleba.substr(0, 1) == "e" && (hamlebi.substr(0, 1) == "d" || hamlebi.substr(0, 1) == "f") && hamle2kontrol - hamle1kontrol == 0) {	// Siyah taşın e  sütunundan d ve f sütunlarına hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(siyah, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}if (hamleba.substr(0, 1) == "e" && hamlebi.substr(0, 1) == "e" && hamle2kontrol - hamle1kontrol == 1) {	// Siyah taşın e  sütununda yukarı hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(siyah, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}
				if (hamleba.substr(0, 1) == "e" && (hamlebi.substr(0, 1) != "d" || hamlebi.substr(0, 1) != "e" || hamlebi.substr(0, 1) != "f") && !(hamle2kontrol - hamle1kontrol == 1 || hamle2kontrol - hamle1kontrol == 0)) {
					cout << " \n Hatali hamle girdiniz  \n";	//Hatalı hamle kontrolü
				}	
				if (hamleba.substr(0, 1) == "f" && (hamlebi.substr(0, 1) == "e" || hamlebi.substr(0, 1) == "g") && hamle2kontrol - hamle1kontrol == 0) {	// Siyah taşın f  sütunundan e ve g sütunlarına hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(siyah, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}if (hamleba.substr(0, 1) == "f" && hamlebi.substr(0, 1) == "f" && hamle2kontrol - hamle1kontrol == 1) {	// Siyah taşın f  sütununda yukarı hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(siyah, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}
				if (hamleba.substr(0, 1) == "f" && (hamlebi.substr(0, 1) != "f" || hamlebi.substr(0, 1) != "e" || hamlebi.substr(0, 1) != "g") && !(hamle2kontrol - hamle1kontrol == 1 || hamle2kontrol - hamle1kontrol == 0)) {
					cout << " \n Hatali hamle girdiniz  \n";	//Hatalı hamle kontrolü
				}
				if (hamleba.substr(0, 1) == "g" && (hamlebi.substr(0, 1) == "f" || hamlebi.substr(0, 1) == "h") && hamle2kontrol - hamle1kontrol == 0) {	// Siyah taşın g  sütunundan f ve h sütunlarına hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(siyah, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}if (hamleba.substr(0, 1) == "g" && hamlebi.substr(0, 1) == "g" && hamle2kontrol - hamle1kontrol == 1) {	// Siyah taşın g  sütununda yukarı hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(siyah, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}
				if (hamleba.substr(0, 1) == "g" && (hamlebi.substr(0, 1) != "f" || hamlebi.substr(0, 1) != "g" || hamlebi.substr(0, 1) != "h") && !(hamle2kontrol - hamle1kontrol == 1 || hamle2kontrol - hamle1kontrol == 0)) {
					cout << " \n Hatali hamle girdiniz  \n";	//Hatalı hamle kontrolü
				}
				if (hamleba.substr(0, 1) == "h" && hamlebi.substr(0, 1) == "h" && hamle2kontrol - hamle1kontrol == 1) {// Siyah taşın g  sütununda yukarı hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(siyah, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}if (hamleba.substr(0, 1) == "h" && hamlebi.substr(0, 1) == "g" && hamle2kontrol - hamle1kontrol == 0) {	// Siyah taşın h  sütunundan g sütununa yukarı hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(siyah, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}
				if (hamleba.substr(0, 1) == "h" && (hamlebi.substr(0, 1) != "h" || hamlebi.substr(0, 1) != "g") && !(hamle2kontrol - hamle1kontrol == 1 || hamle2kontrol - hamle1kontrol == 0)) {
					cout << " \n hata8 \n";		//Hatalı hamle kontrolü
				}
			}
			else if (kontrol1 == 'B' && (hamle2kontrol - hamle1kontrol == 1 || hamle2kontrol - hamle1kontrol == 0)) {
			cout << " \n Hatali hamle girdiniz  \n";		//Hatalı hamle kontrolü
			}

			if (kontrol1 == 'W' && ktext4 == 'W') {
				if (hamleba.substr(0, 1) == "a" && (hamlebi.substr(0, 1) == "a") && hamle1kontrol - hamle2kontrol == 1) {	//Beyaz taşın a sütunundan aşağı hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(beyaz, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}
				if (hamleba.substr(0, 1) == "a" && (hamlebi.substr(0, 1) == "b") && hamle1kontrol - hamle2kontrol == 0) { // Beyaz taşın a sütunundan b sütununa hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(beyaz, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}
				if (hamleba.substr(0, 1) == "a" && (hamlebi.substr(0, 1) != "b" || hamlebi.substr(0, 1) != "a") && !(hamle1kontrol - hamle2kontrol == 1 || hamle2kontrol - hamle1kontrol == 0)) {
					cout << " \n Hatali hamle girdiniz  \n";	//Hatalı hamle kontrolü
				}
				if (hamleba.substr(0, 1) == "b" && (hamlebi.substr(0, 1) == "a" || hamlebi.substr(0, 1) == "c") && hamle1kontrol - hamle2kontrol == 0) {	 // Beyaz taşın b sütunundan a ve c sütununa hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(beyaz, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}if (hamleba.substr(0, 1) == "b" && (hamlebi.substr(0, 1) == "b") && hamle1kontrol - hamle2kontrol == 1) {	//Beyaz taşın b sütunundan aşağı hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(beyaz, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}
				if (hamleba.substr(0, 1) == "b" && (hamlebi.substr(0, 1) != "b" || hamlebi.substr(0, 1) != "a" || hamlebi.substr(0, 1) != "c") && !(hamle1kontrol - hamle2kontrol == 1 || hamle2kontrol - hamle1kontrol == 0)) {
					cout << " \n Hatali hamle girdiniz  \n";	//Hatalı hamle kontrolü
				}
				if (hamleba.substr(0, 1) == "c" && (hamlebi.substr(0, 1) == "b" || hamlebi.substr(0, 1) == "d") && hamle1kontrol - hamle2kontrol == 0) {	 // Beyaz taşın c sütunundan b ve d sütununa hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(beyaz, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}if (hamleba.substr(0, 1) == "c" && (hamlebi.substr(0, 1) == "c") && hamle1kontrol - hamle2kontrol == 1) {	//Beyaz taşın c sütunundan aşağı hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(beyaz, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}
				if (hamleba.substr(0, 1) == "c" && (hamlebi.substr(0, 1) != "b" || hamlebi.substr(0, 1) != "d" || hamlebi.substr(0, 1) != "c") && !(hamle1kontrol - hamle2kontrol == 1 || hamle2kontrol - hamle1kontrol == 0)) {
					cout << " \n Hatali hamle girdiniz  \n";	//Hatalı hamle kontrolü
				}
				if (hamleba.substr(0, 1) == "d" && (hamlebi.substr(0, 1) == "c" || hamlebi.substr(0, 1) == "e") && hamle1kontrol - hamle2kontrol == 0) {	 // Beyaz taşın d sütunundan c ve e sütununa hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(beyaz, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}if (hamleba.substr(0, 1) == "d" && (hamlebi.substr(0, 1) == "d") && hamle1kontrol - hamle2kontrol == 1) {	//Beyaz taşın d sütunundan aşağı hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(beyaz, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}
				if (hamleba.substr(0, 1) == "d" && (hamlebi.substr(0, 1) != "d" || hamlebi.substr(0, 1) != "e" || hamlebi.substr(0, 1) != "c") && !(hamle1kontrol - hamle2kontrol == 1 || hamle2kontrol - hamle1kontrol == 0)) {
					cout << " \n Hatali hamle girdiniz  \n";	//Hatalı hamle kontrolü
				}
				if (hamleba.substr(0, 1) == "e" && (hamlebi.substr(0, 1) == "d" || hamlebi.substr(0, 1) == "f") && hamle1kontrol - hamle2kontrol == 0) {	 // Beyaz taşın e sütunundan d ve f sütununa hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(beyaz, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}if (hamleba.substr(0, 1) == "e" && (hamlebi.substr(0, 1) == "e") && hamle1kontrol - hamle2kontrol == 1) {	//Beyaz taşın e sütunundan aşağı hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(beyaz, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}
				if (hamleba.substr(0, 1) == "e" && (hamlebi.substr(0, 1) != "d" || hamlebi.substr(0, 1) != "e" || hamlebi.substr(0, 1) != "f") && !(hamle1kontrol - hamle2kontrol == 1 || hamle2kontrol - hamle1kontrol == 0)) {
					cout << " \n Hatali hamle girdiniz  \n";	//Hatalı hamle kontrolü
				}
				if (hamleba.substr(0, 1) == "f" && (hamlebi.substr(0, 1) == "e" || hamlebi.substr(0, 1) == "g") && hamle1kontrol - hamle2kontrol == 0) {	 // Beyaz taşın f sütunundan g ve e sütununa hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(beyaz, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}if (hamleba.substr(0, 1) == "f" && (hamlebi.substr(0, 1) == "f") && hamle1kontrol - hamle2kontrol == 1) {		//Beyaz taşın f sütunundan aşağı hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(beyaz, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}
				if (hamleba.substr(0, 1) == "f" && (hamlebi.substr(0, 1) != "f" || hamlebi.substr(0, 1) != "e" || hamlebi.substr(0, 1) != "g") && !(hamle1kontrol - hamle2kontrol == 1 || hamle2kontrol - hamle1kontrol == 0)) {
					cout << " \n Hatali hamle girdiniz  \n";	//Hatalı hamle kontrolü
				}
				if (hamleba.substr(0, 1) == "g" && (hamlebi.substr(0, 1) == "f" || hamlebi.substr(0, 1) == "h") && hamle1kontrol - hamle2kontrol == 0) {	// Beyaz taşın g sütunundan f ve h sütununa hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(beyaz, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}if (hamleba.substr(0, 1) == "g" && (hamlebi.substr(0, 1) == "g") && hamle1kontrol - hamle2kontrol == 1) {	//Beyaz taşın g sütunundan aşağı hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(beyaz, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}
				if (hamleba.substr(0, 1) == "g" && (hamlebi.substr(0, 1) != "f" || hamlebi.substr(0, 1) != "g" || hamlebi.substr(0, 1) != "h") && !(hamle1kontrol - hamle2kontrol == 1 || hamle2kontrol - hamle1kontrol == 0)) {
					cout << " \n Hatali hamle girdiniz  \n";	//Hatalı hamle kontrolü
				}
				if (hamleba.substr(0, 1) == "h" && (hamlebi.substr(0, 1) == "h") && hamle1kontrol - hamle2kontrol == 1) {	//Beyaz taşın h sütunundan aşağı hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(beyaz, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}
				if (hamleba.substr(0, 1) == "h" && (hamlebi.substr(0, 1) == "g") && hamle1kontrol - hamle2kontrol == 0) {	//Beyaz taşın h sütunundan g sütununa hareketi
					ekranaekleme("\0", hamlekonum1);
					ekranaekleme(beyaz, hamlekonum2);
					sirakontrol++;
					damakontrol(hamlekonum2);
					hamledosya(hamle, sirakontrol);
				}
				if (hamleba.substr(0, 1) == "h" && (hamlebi.substr(0, 1) != "h" || hamlebi.substr(0, 1) != "g") && !(hamle1kontrol - hamle2kontrol == 1 || hamle2kontrol - hamle1kontrol == 0)) {
					cout << " \n Hatali hamle girdiniz  \n";	//Hatalı hamle kontrolü
				}
			}
			else if (kontrol1 == 'W' && (hamle1kontrol - hamle2kontrol == 1 || hamle2kontrol - hamle1kontrol == 0)) {
				cout << " \n Hatali hamle girdiniz  \n";		//Hatalı hamle kontrolü
			}
		}
		cout << "\n";
		if (sirakontrol % 2 == 1) { // Sıranın kimde olduğunu kontrol edip tahtaya işler
			ekranaekleme(beyaz, 1128);
		}
		else if (sirakontrol % 2 == 0) {	// Sıranın kimde olduğunu kontrol edip tahtaya işler
			ekranaekleme(siyah, 1128);
		}
		
	}
	
}

int main() {
	int point[64] = { 1,10,19,28,37,46,55,64,151,160,169,178,187,196,205,214,301,310,319,328,337,346,355,364,451,460,469,478,487,496,505,514,601,610,619,628,637,646,655,664,751,760,769,778,787,796,805,814,
	901,910,919,928,937,946,955,964,1051,1060,1069,1078,1087,1096,1105,1114 }; //Tüm karelerin konumunu tutan int array
	const char* siyah = "B"; // Siyah taşların renklerini tutan değişken
	const char* damasiyah = "BB"; // Siyah dama taşların renklerini tutan değişken
	const char* damabeyaz = "WW"; // Beyaz dama taşların renklerini tutan değişken
	const char* beyaz = "W" ;// Beyaz taşların renklerini tutan değişken
	ifstream file1;
	int menukontrol; // Menü kontrolü için tanımlanan değişken
	kare a1, a2, a3, a4, a5, a6, a7, a8, b1, b2, b3, b4, b5, b6, b7, b8, c1, c2, c3, c4, c5, c6, c7, c8, d1, d2, d3, d4, d5, d6, d7, d8; // Her kare için struct tanımları
	kare f1, f2, f3, f4, f5, f6, f7, f8, g1, g2, g3, g4, g5, g6, g7, g8, h1, h2, h3, h4, h5, h6, h7, h8, e1, e2, e3, e4, e5, e6, e7, e8; // Her kare için struct tanımları
	a1.ad = "a1";
	a1.konum = 1051;       // Her kare için struct tanımları
	a2.ad = "a2";
	a2.konum = 901;
	a3.ad = "a3";
	a3.konum = 751;
	a4.ad = "a4";
	a4.konum = 601;
	a5.ad = "a5";
	a5.konum = 451;
	a6.ad = "a6";
	a6.konum = 301;
	a7.ad = "a7";
	a7.konum = 151;
	a8.ad = "a8";
	a8.konum = 1;
	b1.ad = "b1";
	b2.ad = "b2";
	b3.ad = "b3";
	b4.ad = "b4";
	b5.ad = "b5";
	b6.ad = "b6";
	b7.ad = "b7";
	b8.ad = "b8";
	b1.konum = 1060;
	b2.konum = 910;
	b3.konum = 760;
	b4.konum = 610;
	b5.konum = 460;
	b6.konum = 310;
	b7.konum = 160;
	b8.konum = 10;
	c1.ad = "c1";
	c2.ad = "c2";
	c3.ad = "c3";
	c4.ad = "c4";
	c5.ad = "c5";
	c6.ad = "c6";
	c7.ad = "c7";
	c8.ad = "c8";
	c1.konum = 1069;
	c2.konum = 919;
	c3.konum = 769;
	c4.konum = 619;
	c5.konum = 469;
	c6.konum = 319;
	c7.konum = 169;
	c8.konum = 19;
	d1.ad = "d1";
	d2.ad = "d2";
	d3.ad = "d3";
	d4.ad = "d4";
	d5.ad = "d5";
	d6.ad = "d6";
	d7.ad = "d7";
	d8.ad = "d8";
	d1.konum = 1078;
	d2.konum = 928;
	d3.konum = 778;
	d4.konum = 628;
	d5.konum = 478;
	d6.konum = 328;
	d7.konum = 178;
	d8.konum = 28;
	e1.ad = "e1";
	e2.ad = "e2";
	e3.ad = "e3";
	e4.ad = "e4";
	e5.ad = "e5";
	e6.ad = "e6";
	e7.ad = "e7";
	e8.ad = "e8";
	e1.konum = 1087;
	e2.konum = 937;
	e3.konum = 787;
	e4.konum = 637;
	e5.konum = 487;
	e6.konum = 337;
	e7.konum = 187;
	e8.konum = 37;
	f1.ad = "f1";
	f2.ad = "f2";
	f3.ad = "f3";
	f4.ad = "f4";
	f5.ad = "f5";
	f6.ad = "f6";
	f7.ad = "f7";
	f8.ad = "f8";
	f1.konum = 1096;
	f2.konum = 946;
	f3.konum = 796;
	f4.konum = 646;
	f5.konum = 496;
	f6.konum = 346;
	f7.konum = 196;
	f8.konum = 46;
	g1.ad = "g1";
	g2.ad = "g2";
	g3.ad = "g3";
	g4.ad = "g4";
	g5.ad = "g5";
	g6.ad = "g6";
	g7.ad = "g7";
	g8.ad = "g8";
	g1.konum = 1105;
	g2.konum = 955;
	g3.konum = 805;
	g4.konum = 655;
	g5.konum = 505;
	g6.konum = 355;
	g7.konum = 205;
	g8.konum = 55;
	h1.ad = "h1";
	h2.ad = "h2";
	h3.ad = "h3";
	h4.ad = "h4";
	h5.ad = "h5";
	h6.ad = "h6";
	h7.ad = "h7";
	h8.ad = "h8";
	h1.konum = 1114;
	h2.konum = 964;
	h3.konum = 814;
	h4.konum = 664;
	h5.konum = 514;
	h6.konum = 364;
	h7.konum = 214;
	h8.konum = 64;
	cout << "Dama Oyununa hosgeldiniz \n"; // Menü kontrolleri
	cout << "Yeni oyun icin 1 \n";
	cout << "Eski oyuna devam etmek icin 2 \n";
	cout << "Oyunu kapatmak icin 3 giriniz \n";
	cin >> menukontrol;
	if (menukontrol == 1) { // Menü kontrolü yaparak oyunun oynanabilirliğini sağlama
		yenioyun(); // Yeni oyun başlatan fonksiyon
		Oyun(a1, a2, a3, a4, a5, a6, a7, a8, b1, b2, b3, b4, b5, b6, b7, b8, c1, c2, c3, c4, c5, c6, c7, c8, d1, d2, d3, d4, d5, d6, d7, d8,
			f1, f2, f3, f4, f5, f6, f7, f8, g1, g2, g3, g4, g5, g6, g7, g8, h1, h2, h3, h4, h5, h6, h7, h8, e1, e2, e3, e4, e5, e6, e7, e8, siyah, beyaz, damasiyah, damabeyaz); // Oyunu içeren fonksiyon
	}
	else if (menukontrol == 2) {
		Oyun(a1, a2, a3, a4, a5, a6, a7, a8, b1, b2, b3, b4, b5, b6, b7, b8, c1, c2, c3, c4, c5, c6, c7, c8, d1, d2, d3, d4, d5, d6, d7, d8,
			f1, f2, f3, f4, f5, f6, f7, f8, g1, g2, g3, g4, g5, g6, g7, g8, h1, h2, h3, h4, h5, h6, h7, h8, e1, e2, e3, e4, e5, e6, e7, e8, siyah, beyaz, damasiyah, damabeyaz);
	}
	else if (menukontrol == 3) {
		cout << "İYi GUNLER";
		return 0;
	}
	return 0;
}
