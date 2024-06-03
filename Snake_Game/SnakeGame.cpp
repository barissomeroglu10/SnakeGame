#include <iostream>

#include <conio.h> 
// console input/output kelimelerinin kısaltmasıdır
// C/C++ da konsoldan girdi almak ve konsola çıktı vermek için kullanılır
// _kbhit() ve _getch() fonksiyonları için gereken kütüphanedir

#include <Windows.h>
// Windows işletim sistemiyle ilgili işlevleri ve yapıları içerir
// Windows işletim sistemi özelliklerini kullanarak program geliştirmemize olanak sağlar
// sleep() fonksiyonu için gereken kütüphanedir

#include <ctime>
// srand(NULL) fonksiyonu için gereken kütüphanedir

#include <fstream> 
// Dosya işlemleri için gereken kütüphanedir

using namespace std;

// Fonksiyon prototiplerini yazma aşaması
void Kurulum();
void Ciz();
void Girdi();
void Mantik();
int EnYuksekPuaniOku();
void EnYuksekPuaniYaz(int);

// Global değişkenleri tanımlama aşaması

bool oyunBitti; // Oyunun bitip bitmediğini kontrol eden değişkendir

// const, constant kelimesinin kısaltmasıdır ve C++ programlama dilinde sabit bir değer tanımlamak için kullanılan bir belirteçtir
// yani const kullanmamızın nedeni bu değişkenlerin oyun boyunca sabit kalmasını istememizdir
const int genislik = 20; // Oyun alanının genişliğini belirleyen sabittir
const int yukseklik = 20; // Oyun alanının yüksekliğini belirleyen sabittir

int x, y, meyveX, meyveY, puan; // Yılanın ve meyvenin kordinatları bu değişkenlerde tutulur, puan değişkeni ise puanı tutar

int kuyrukX[100], kuyrukY[100]; // Yılanın kuyruğunun her bir parçasının kordinatlarını tutan dizilerdir

int kuyrukUzunlugu; // Yılanın kuyruk uzunluğunu tutan değişkendir


/*
enum = enumeration kelimesinin kısaltmasıdır ve sabit bir grup ile ilişkili isimlendirilmiş
sabitleri tanımlamak için kullanılır.
enum yapısı, bu sabitleri daha anlamlı ve okunabilir hale getirir. Bu, kodun okunabilirliğini ve bakımını kolaylaştırır.
*/

enum Yon { DUR = 0, SOL, SAG, YUKARI, ASAGI };
Yon yon;
// enum kullanmamızın nedeni yönleri daha anlamlı ve okunabilir hale getirmektir
// Yon: yılanın yönlerini belirlemek için kullanılan enum'dur
// yon: bir değişkendir, bu değişken yılanın mevcut yönünü tutar ve yalnızca Yon enum türünden bir değer alabilir

int OyunModu;
// Kullanıcının oyun modunu tutan değişken



int main()
{
	// Oyun hızını kullanıcı belirler
	int OyunHizi;

	cout << "Hizli oyun modu icin 50 giriniz\n";
	cout << "Orta hizli oyun modu icin 120 giriniz\n";
	cout << "Yavas oyun modu icin 150 giriniz\n\n";

	cout << "Lutfen Oynamak Istedginiz Oyun Hizini Giriniz: ";
	cin >> OyunHizi;

	system("cls");

	// Kullanıcı oyun modunu belirler
	cout << "Duvarli Oyun Modu Icin 1 giriniz\n";
	cout << "Duvarsiz Oyun Modu Icin 2 giriniz\n\n";

	cout << "Oynamak Istediginiz Oyun Modunu Seciniz: ";
	cin >> OyunModu;

	int enYuksekPuan = EnYuksekPuaniOku();

	Kurulum(); // Oyunun kurulumunu sağlar

	while (!oyunBitti) // Oyun bitene kadar döngüyü devam ettiren koşullu döngü yapısı
	{
		Ciz(); // Oyun alanını çizer

		Girdi(); // Kullanıcıdan girdileri alır

		Mantik(); // Oyunun oynanma mantığını işler

		Sleep(OyunHizi);
		// Yılanın hareket hızını ayarlar
		// Belli bir süre boyunca programın çalışmasını duraklatmak için kullanılır
	}

	if (puan > enYuksekPuan)
	{
		enYuksekPuan = puan;

		EnYuksekPuaniYaz(enYuksekPuan);
	}

	cout << "En Yuksek Puan: " << enYuksekPuan << endl;

	return 0;
}



void Kurulum() // Oyunun başlangıç ayarlarını yapar
{
	srand(time(NULL));

	oyunBitti = false; // Oyun başlarken bitmiş değildir

	yon = DUR; // Yılanın başlangıçta hareket etmemesini sağlar

	x = genislik / 2; // Yılanın başının x kordinatının oyun alanının ortasında başlamasını sağlar
	y = yukseklik / 2; // Yılanın başının y kordinatının oyun alanının ortasında başlamasını sağlar

	// Bu iki satır ile meyvenin konumunun her zaman farklı olması sağlanır
	meyveX = rand() % genislik; // Meyvenin x kordinatını rastgele belirler
	meyveY = rand() % yukseklik; // Meyvenin y kordinatını rastgele belirler

	puan = 0; // Başlangıçta puan sıfırdır
}

void Ciz() // Oyun alanını ve yılanı çizen fonksiyondur
{
	system("cls"); // Konsol ekranını temizler

	// Üst duvarı çizen döngü
	for (int i = 0; i < genislik + 2; i++) // genislik + 2 olmasının nedeni sol ve sağ duvarların da hesaba katılmasıdır 
	{
		cout << "#";
	}

	cout << endl;

	// Oyun alanını çizen deyim
	for (int i = 0; i < yukseklik; i++)
	{
		for (int j = 0; j < genislik; j++)
		{
			if (j == 0)
			{
				cout << "#"; // Sol duvarı çizer 0-0, 1-0, 2-0, 3-0....18-0, 19-0
			}

			if (i == y && j == x)
			{
				cout << "0"; // Yılanın başını çizer
			}

			else if (i == meyveY && j == meyveX)
			{
				cout << "+"; // Meyveyi çizer
			}

			else
			{
				bool yazdir = false;

				for (int k = 0; k < kuyrukUzunlugu; k++)
				{
					if (kuyrukX[k] == j && kuyrukY[k] == i)
					{
						cout << "o"; // Yılanın kuyruğunu çizer

						yazdir = true;
					}
				}

				if (!yazdir)
					cout << " "; // Boş alanı çizer
			}

			if (j == genislik - 1)
				cout << "#"; // Sağ duvarı çizer 0-19, 1-19, 2-19 ... 18-19
		}

		cout << endl;
	}

	// Alt duvarı çizen deyim
	for (int i = 0; i < genislik + 2; i++) // genislik + 2 olmasının nedeni sol ve sağ duvarların da hesaba katılmasıdır
	{
		cout << "#";
	}

	cout << endl;

	// Puanı ekrana yazan deyim
	cout << "Mevcut Puan: " << puan << endl;
}

void Girdi()
{
	if (_kbhit()) // Klavyeden bir tuşa basılıp basılmadığını kontrol eder
	{
		switch (_getch()) // Basılan tuşun hangi tuş olduğunu kontrol eder
		{
		case 'a':
			if(yon != SAG)
				yon = SOL; // a tuşuna basıldığında yılan sola gider
			break;

		case 'd':
			if(yon != SOL)
				yon = SAG; // d tuşuna basıldığında yılan sağa gider
			break;

		case 'w':
			if(yon != ASAGI)
				yon = YUKARI; // w tuşuna basıldığında yılan yukarı gider
			break;

		case 's':
			if(yon != YUKARI)
				yon = ASAGI; // s tuşuna basıldığında yılan aşağı gider
			break;

		case 'x':
			oyunBitti = true; // x tuşuna basıldığında oyun biter
			break;

		}
	}
}

void Mantik() // Oyunun mantığını ayarlayan fonksiyon
{
	// Kuyruğu güncellemek için önceki pozisyonları kaydeder
	int oncekiX = kuyrukX[0];
	int oncekiY = kuyrukY[0];
	int onceki2X, onceki2Y;
	kuyrukX[0] = x;
	kuyrukY[0] = y;

	for (int i = 1; i < kuyrukUzunlugu; i++)
	{
		// swap yapılır
		onceki2X = kuyrukX[i];
		onceki2Y = kuyrukY[i];

		kuyrukX[i] = oncekiX;
		kuyrukY[i] = oncekiY;

		oncekiX = onceki2X;
		oncekiY = onceki2Y;
	}

	// Yönlere göre yılanın hareketini sağlar, burada "ekran kordinat sistemi" geçerlidir
	switch (yon)
	{
	case SOL:
		x--; // Yılan sola gider
		break;

	case SAG:
		x++; // Yılan sağa gider
		break;

	case YUKARI:
		y--; // Yılan yukarı gider
		break;

	case ASAGI:
		y++; // Yılan aşağı gider
		break;
	}

	if (OyunModu == 1)
	{
		if (x >= genislik || x < 0 || y >= yukseklik || y < 0)
			oyunBitti = true;
	}

	else if (OyunModu == 2)
	{
		// Yılanın oyun alanında kalmasını ve zıt duvardan çıkmasını sağlar
		if (x >= genislik)
		{
			x = 0;
		}

		else if (x < 0)
		{
			x = genislik - 1;
		}

		if (y >= yukseklik)
		{
			y = 0;
		}

		else if (y < 0)
		{
			y = yukseklik - 1;
		}
	}

	// Yılanın kuyruğuna çarpıp çarpmadığı kontrol edilir
	for (int i = 0; i < kuyrukUzunlugu; i++)
	{
		if (kuyrukX[i] == x && kuyrukY[i] == y)
		{
			oyunBitti = true;
		}
	}

	// Yılanın meyveyi yiyip yemediği kontrol edilir
	if (x == meyveX && y == meyveY)
	{
		puan += 10; // Her meyve yenildiğinde puan 10 artar

		meyveX = rand() % genislik; // Meyvenin yeni konumu rastgele belirlenir (x ekseni için)
		meyveY = rand() % yukseklik; // Meyvenin yeni konumu rastgele belirlenir (y ekseni için)

		kuyrukUzunlugu++; // Her meyve yenildiğinde yılanın kuyruğu uzatılır

	}
}

int EnYuksekPuaniOku() // En yuksek puanı dosyadan okuyan fonksiyon
{
	ifstream dosya("en_yuksek_puan.txt"); // En yüksek puanı tutacak olan bir txt dosyası açılır

	int enYuksekPuan = 0; // Başlangıçta en yuksek puan 0'dır

	if (dosya.is_open())
	{
		dosya >> enYuksekPuan; // Dosyadan en yüksek puan okunur

		dosya.close();
	}

	return enYuksekPuan;
}

void EnYuksekPuaniYaz(int puan) // Eğer puan değeri en yüksek ise onu ekrana yazar
{
	ofstream dosya("en_yuksek_puan.txt");

	if (dosya.is_open())
	{
		dosya << puan; // Dosyadan en yüksek puan yazılır

		dosya.close();
	}
}


