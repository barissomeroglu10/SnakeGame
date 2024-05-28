#include <iostream>
#include <conio.h> // _kbhit() ve _getch() fonksiyonları için gereken kütüphaneyi ekler.
#include <windows.h> // Sleep() fonksiyonu için gereken kütüphaneyi ekler.
#include <ctime>

using namespace std;

// oyunBitti: Oyunun bitip bitmediğini kontrol eder.
bool oyunBitti;

// genislik ve yukseklik: Oyun alanının genişliğini ve yüksekliğini belirleyen sabitler.
// const kullanmamızın nedeni bu değişkenlerin program boyunca değişmeyeceğini belirtmektir.
const int genislik = 20;
const int yukseklik = 20;

// Yılanın ve meyvenin koordinatlarını tutan değişkenler.
int x, y, meyveX, meyveY, puan;

// Yılanın kuyruğunun her bir segmentinin koordinatlarını tutan diziler.
int kuyrukX[100], kuyrukY[100];

// Yılanın kuyruğunun uzunluğunu tutan değişken.
int kuyrukUzunlugu;

// Yon: Yılanın yönlerini belirlemek için kullanılan bir enum.
// Enum kullanmamızın nedeni, yönleri daha anlamlı ve okunabilir hale getirmektir.
enum Yon { DUR = 0, SOL, SAG, YUKARI, ASAGI };
Yon yon;

// Kurulum: Oyunun başlangıç ayarlarını yapan fonksiyon.
void Kurulum()
{
    srand(time(0));
    oyunBitti = false; // Oyun başlarken bitmiş değil.
    yon = DUR; // Yılan başlangıçta hareket etmiyor.
    x = genislik / 2; // Yılanın başı oyun alanının ortasında başlar.
    y = yukseklik / 2; // Yılanın başı oyun alanının ortasında başlar.
    meyveX = rand() % genislik; // Meyvenin x koordinatı rastgele belirlenir.
    meyveY = rand() % yukseklik; // Meyvenin y koordinatı rastgele belirlenir.
    puan = 0; // Başlangıç puanı sıfır.
}

// Ciz: Oyun alanını ve yılanı çizen fonksiyon.
void Ciz()
{
    system("cls"); // Ekranı temizler.

    // Üst duvarı çizer.
    for (int i = 0; i < genislik + 2; i++)
        cout << "#";
    cout << endl;

    // Oyun alanının içini çizer.
    for (int i = 0; i < yukseklik; i++)
    {
        for (int j = 0; j < genislik; j++)
        {
            if (j == 0)
                cout << "#"; // Sol duvarı çizer.

            if (i == y && j == x)
                cout << "O"; // Yılanın başını çizer.
            else if (i == meyveY && j == meyveX)
                cout << "+"; // Meyveyi çizer.
            else
            {
                bool yazdir = false;
                for (int k = 0; k < kuyrukUzunlugu; k++)
                {
                    if (kuyrukX[k] == j && kuyrukY[k] == i)
                    {
                        cout << "o"; // Yılanın kuyruğunu çizer.
                        yazdir = true;
                    }
                }
                if (!yazdir)
                    cout << " "; // Boş alanı çizer.
            }

            if (j == genislik - 1)
                cout << "#"; // Sağ duvarı çizer.
        }
        cout << endl;
    }

    // Alt duvarı çizer.
    for (int i = 0; i < genislik + 2; i++)
        cout << "#";
    cout << endl;

    // Puanı ekrana yazdırır.
    cout << "Puan:" << puan << endl;
}

// Girdi: Kullanıcıdan gelen girdileri işleyen fonksiyon.
void Girdi()
{
    if (_kbhit()) // Klavyeden bir tuşa basıldığını kontrol eder.
    {
        switch (_getch()) // Basılan tuşu alır ve kontrol eder.
        {
        case 'a':
            yon = SOL; // 'a' tuşuna basılırsa yılan sola gider.
            break;
        case 'd':
            yon = SAG; // 'd' tuşuna basılırsa yılan sağa gider.
            break;
        case 'w':
            yon = YUKARI; // 'w' tuşuna basılırsa yılan yukarı gider.
            break;
        case 's':
            yon = ASAGI; // 's' tuşuna basılırsa yılan aşağı gider.
            break;
        case 'x':
            oyunBitti = true; // 'x' tuşuna basılırsa oyun biter.
            break;
        }
    }
}

// Mantik: Oyunun mantığını işleyen fonksiyon.
void Mantik()
{
    // Kuyruğu güncellemek için önceki pozisyonları kaydeder.
    int oncekiX = kuyrukX[0];
    int oncekiY = kuyrukY[0];
    int onceki2X, onceki2Y;
    kuyrukX[0] = x;
    kuyrukY[0] = y;
    for (int i = 1; i < kuyrukUzunlugu; i++)
    {
        onceki2X = kuyrukX[i];
        onceki2Y = kuyrukY[i];
        kuyrukX[i] = oncekiX;
        kuyrukY[i] = oncekiY;
        oncekiX = onceki2X;
        oncekiY = onceki2Y;
    }

    // Yönlere göre yılanın hareketini sağlar.
    switch (yon)
    {
    case SOL:
        x--; // Yılan sola gider.
        break;
    case SAG:
        x++; // Yılan sağa gider.
        break;
    case YUKARI:
        y--; // Yılan yukarı gider.
        break;
    case ASAGI:
        y++; // Yılan aşağı gider.
        break;
    default:
        break;
    }

    // Yılanın oyun alanının dışına çıkmasını engeller ve zıt duvardan yılanın çıkmasını sağlar.
    if (x >= genislik) x = 0; else if (x < 0) x = genislik - 1;
    if (y >= yukseklik) y = 0; else if (y < 0) y = yukseklik - 1;

    // Yılanın kuyruğuna çarpıp çarpmadığını kontrol eder.
    for (int i = 0; i < kuyrukUzunlugu; i++)
        if (kuyrukX[i] == x && kuyrukY[i] == y)
            oyunBitti = true;

    // Yılanın meyveyi yediğini kontrol eder.
    if (x == meyveX && y == meyveY)
    {
        puan += 10; // Puanı artırır.
        meyveX = rand() % genislik; // Yeni meyve konumunu belirler.
        meyveY = rand() % yukseklik; // Yeni meyve konumunu belirler.
        kuyrukUzunlugu++; // Yılanın kuyruğunu uzatır.
    }
}

// Ana fonksiyon
int main()
{
    Kurulum(); // Oyunun başlangıç ayarlarını yapar.
    while (!oyunBitti) // Oyun bitene kadar döngü devam eder.
    {
        Ciz(); // Oyun alanını çizer.
        Girdi(); // Kullanıcı girdilerini alır.
        Mantik(); // Oyunun mantığını işler.
        Sleep(200); // 200 milisaniye bekler.
    }
    return 0;
}

