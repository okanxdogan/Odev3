#include <stdio.h>
#include <stdlib.h>
#include "can_queue.h"

// 1. Tek bir sensör mesajının yapısı
typedef struct {
    int mesaj_id;          
    float veri;            
    char gonderen[30];
} CAN_Mesaj;

// 2. Mesajların beklediği kuyruk yapısı
typedef struct {
    CAN_Mesaj *mesajlar;    
    int kapasite;           
    int front;              
    int rear;               
    int count;              
} MesajKuyrugu;

int main() {
    int kapasite;
    int secim = 0;
    MesajKuyrugu q;

    // BAŞLANGIÇ: Kapasite belirleme
    printf("[SİSTEM] Lütfen CAN Bus mesaj kuyruğu kapasitesini giriniz: ");
    scanf("%d", &kapasite);
    
    // Aşağıdakilerin çalışması için can_queue_init(&q, kapasite) fonksiyonunun can_queue.c'de yazılması gerekiyor.
    q.kapasite = kapasite;
    q.mesajlar = (CAN_Mesaj*)malloc(q.kapasite * sizeof(CAN_Mesaj));
    q.front = 0;
    q.rear = -1;
    q.count = 0;

    printf("[BİLGİ] %d kapasiteli dinamik mesaj kuyruğu bellekte oluşturuldu!\n", kapasite);

    // Ana menü döngüsü
    while (secim != 4) {
        printf("\n--- CAN BUS İLETİŞİM SİSTEMİ ---\n");
        printf("1. Sensörden Mesaj Üret (Enqueue)\n");
        printf("2. Bekleyen İlk Mesajı İşle (Dequeue)\n");
        printf("3. Bekleyen Mesajları Göster\n");
        printf("4. Çıkış (Bellek Temizle)\n");
        printf("Seçiminiz: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                // enqueue(&q) fonksiyonu çağrılacak.
                break;
            case 2:
                // dequeue(&q) fonksiyonu çağrılacak.
                break;
            case 3:
                // printQueue(&q) fonksiyonu çağrılacak.
                break;
            case 4:
                free(q.mesajlar);
                printf("[BİLGİ] Dinamik bellek (RAM) temizleniyor...\n");
                printf("[BİLGİ] Sistem güvenli bir şekilde kapatıldı.\n");
                break;
            default:
                printf("[HATA] Geçersiz seçim!\n");
                break;
        }
    }

    return 0;
}