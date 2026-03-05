#ifndef CAN_QUEUE_H
#define CAN_QUEUE_H

// ─────────────────────────────────────────────
//  Struct Tanımlamaları
// ─────────────────────────────────────────────

// Tek bir sensör mesajının yapısı
typedef struct {
    int   mesaj_id;      // Örn: 101 (Hız), 202 (Batarya)
    float veri;          // Örn: 45.5 (Derece veya km/s)
    char  gonderen[30];  // Örn: "Motor_Sicaklik_Sensoru"
} CAN_Mesaj;

// Mesajların beklediği kuyruk yapısı (Dinamik Dizi ile)
typedef struct {
    CAN_Mesaj *mesajlar; // Dinamik olarak tahsis edilecek dizi pointer'ı
    int kapasite;        // Kullanıcının belirlediği maksimum kapasite
    int front;           // Kuyruğun başı (işlenecek ilk mesajın indeksi)
    int rear;            // Kuyruğun sonu (yeni eklenecek mesajın indeksi)
    int count;           // Kuyruktaki anlık mesaj sayısı
} MesajKuyrugu;

// ─────────────────────────────────────────────
//  Fonksiyon Prototipleri
// ─────────────────────────────────────────────

/**
 * @brief  Dinamik bellek tahsisi yaparak kuyruğu başlatır.
 * @param  kapasite  Kuyruğun tutabileceği maksimum mesaj sayısı.
 * @return Başarıyla oluşturulan MesajKuyrugu nesnesi.
 */
MesajKuyrugu kuyruk_olustur(int kapasite);

/**
 * @brief  Kuyruğa yeni bir CAN mesajı ekler (Enqueue).
 *         Kuyruk doluysa hata mesajı basar.
 * @param  kuyruk  İşlem yapılacak kuyruk pointer'ı.
 * @param  mesaj   Eklenecek CAN_Mesaj nesnesi.
 */
void enqueue(MesajKuyrugu *kuyruk, CAN_Mesaj mesaj);

/**
 * @brief  Kuyruktaki ilk mesajı çıkarır ve işler (Dequeue).
 *         Kuyruk boşsa uyarı mesajı basar.
 * @param  kuyruk  İşlem yapılacak kuyruk pointer'ı.
 */
void dequeue(MesajKuyrugu *kuyruk);

/**
 * @brief  Kuyruktaki tüm mesajları front'tan rear'a sırayla ekrana basar.
 *         Kuyruk boşsa uyarı mesajı basar.
 * @param  kuyruk  İşlem yapılacak kuyruk pointer'ı.
 */
void kuyruk_yazdir(const MesajKuyrugu *kuyruk);

/**
 * @brief  malloc ile ayrılan dinamik belleği serbest bırakır.
 * @param  kuyruk  İşlem yapılacak kuyruk pointer'ı.
 */
void kuyruk_serbest_birak(MesajKuyrugu *kuyruk);

#endif /* CAN_QUEUE_H */
