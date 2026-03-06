#ifndef CAN_QUEUE_H
#define CAN_QUEUE_H

// 1. Tek bir sensör mesajının yapısı 
typedef struct {
    int mesaj_id;          // mesaj ID'si 
    float veri;            // veri  
    char gonderen[30];     // gönderen sensör adı 
} CAN_Mesaj;

// 2. Mesajların beklediği kuyruk yapısı 
typedef struct {
    CAN_Mesaj *mesajlar;    // dinamik dizi pointer'ı 
    int kapasite;           // maksimum kapasite 
    int front;              // kuyruğun başı 
    int rear;               // kuyruğun sonu 
    int count;              // anlık mesaj sayısı 
} MesajKuyrugu;

// --- Fonksiyon Prototipleri ---

void initQueue(MesajKuyrugu *q, int kapasite); // bellek ayırma (malloc) 
void enqueue(MesajKuyrugu *q);                // ekleme 
void dequeue(MesajKuyrugu *q);                // çıkarma 
void printQueue(MesajKuyrugu *q);              // yazdırma 
void freeQueue(MesajKuyrugu *q);               // bellek temizleme (free) 

#endif