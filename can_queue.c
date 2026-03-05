#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "can_queue.h"

// ─────────────────────────────────────────────
//  Kuyruğu Oluştur (Dynamic Memory Allocation)
// ─────────────────────────────────────────────
MesajKuyrugu kuyruk_olustur(int kapasite) {
    MesajKuyrugu kuyruk;

    kuyruk.mesajlar = (CAN_Mesaj *)malloc(kapasite * sizeof(CAN_Mesaj));

    if (kuyruk.mesajlar == NULL) {
        printf("[HATA] Bellek tahsisi basarisiz! Program kapatiliyor.\n");
        exit(EXIT_FAILURE);
    }

    kuyruk.kapasite = kapasite;
    kuyruk.front    = 0;
    kuyruk.rear     = 0;
    kuyruk.count    = 0;

    printf("[BILGI] %d kapasiteli dinamik mesaj kuyrugu bellekte olusturuldu!\n\n", kapasite);
    return kuyruk;
}

// ─────────────────────────────────────────────
//  Enqueue — Kuyruğa Mesaj Ekle
// ─────────────────────────────────────────────
void enqueue(MesajKuyrugu *kuyruk, CAN_Mesaj mesaj) {
    // Overflow kontrolü
    if (kuyruk->count == kuyruk->kapasite) {
        printf("[HATA] CAN Bus hatti dolu! Kapasite (%d) asildi. Yeni mesaj eklenemez.\n",
               kuyruk->kapasite);
        return;
    }

    // Dairesel dizi mantığıyla rear pozisyonuna yaz
    kuyruk->mesajlar[kuyruk->rear] = mesaj;

    // rear'ı bir ilerlet; kapasiteye ulaşınca başa dön (circular buffer)
    kuyruk->rear = (kuyruk->rear + 1) % kuyruk->kapasite;
    kuyruk->count++;

    printf("[BILGI] Mesaj kuyruga eklendi. (Siradaki mesaj sayisi: %d)\n", kuyruk->count);
}

// ─────────────────────────────────────────────
//  Dequeue — Kuyruktaki İlk Mesajı İşle
// ─────────────────────────────────────────────
void dequeue(MesajKuyrugu *kuyruk) {
    // Underflow kontrolü
    if (kuyruk->count == 0) {
        printf("[BILGI] Islenecek yeni mesaj bulunmuyor.\n");
        return;
    }

    // front'taki mesajı oku
    CAN_Mesaj islenen = kuyruk->mesajlar[kuyruk->front];

    // front'ı bir ilerlet; kapasiteye ulaşınca başa dön
    kuyruk->front = (kuyruk->front + 1) % kuyruk->kapasite;
    kuyruk->count--;

    printf("[ISLENDI] %s (ID: %d) sensorunden gelen '%.2f' verisi ana bilgisayar tarafindan islendi.\n",
           islenen.gonderen, islenen.mesaj_id, islenen.veri);
    printf("[BILGI] Kuyrukta kalan mesaj sayisi: %d\n", kuyruk->count);
}

// ─────────────────────────────────────────────
//  Print Queue — Bekleyen Mesajları Göster
// ─────────────────────────────────────────────
void kuyruk_yazdir(const MesajKuyrugu *kuyruk) {
    // Underflow kontrolü
    if (kuyruk->count == 0) {
        printf("[BILGI] Islenecek yeni mesaj bulunmuyor.\n");
        return;
    }

    printf("[BEKLEYEN MESAJLAR - Toplam: %d]\n", kuyruk->count);

    // front'tan başlayıp count kadar ilerle (dairesel)
    for (int i = 0; i < kuyruk->count; i++) {
        int index = (kuyruk->front + i) % kuyruk->kapasite;
        printf("  %d. %s (ID: %d) - Veri: %.2f\n",
               i + 1,
               kuyruk->mesajlar[index].gonderen,
               kuyruk->mesajlar[index].mesaj_id,
               kuyruk->mesajlar[index].veri);
    }
}

// ─────────────────────────────────────────────
//  Belleği Serbest Bırak
// ─────────────────────────────────────────────
void kuyruk_serbest_birak(MesajKuyrugu *kuyruk) {
    free(kuyruk->mesajlar);      // Dinamik diziyi RAM'e iade et
    kuyruk->mesajlar = NULL;     // Dangling pointer'ı önle
    kuyruk->kapasite = 0;
    kuyruk->front    = 0;
    kuyruk->rear     = 0;
    kuyruk->count    = 0;
    printf("[BILGI] Dinamik bellek (RAM) temizlendi.\n");
}
