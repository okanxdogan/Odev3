#include <stdio.h>
#include <stdlib.h>
#include "can_queue.h"

int main() {
    int kapasite;
    int secim = 0;
    MesajKuyrugu q;

    // 1. BAŞLANGIÇ: Kapasiteyi belirle ve belleği ayır
    printf("[SİSTEM] Lütfen CAN Bus mesaj kuyruğu kapasitesini giriniz: ");
    scanf("%d", &kapasite);

    initQueue(&q, kapasite);
    printf("[BİLGİ] %d kapasiteli dinamik mesaj kuyruğu bellekte oluşturuldu!\n", kapasite);

    // 2. ANA MENÜ DÖNGÜSÜ
    while (secim != 4) {
        printf("\nCAN BUS İLETİŞİM SİSTEMİ\n");
        printf("1. Sensörden Mesaj Üret (Kuyruğa Ekle)\n");
        printf("2. Bekleyen İlk Mesajı İşle (Kuyruktan Çıkar)\n");
        printf("3. Bekleyen Mesajları Göster\n");
        printf("4. Çıkış\n");
        printf("Seçiminiz: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                enqueue(&q);
                break;
            case 2:
                dequeue(&q);
                break;
            case 3:
                printQueue(&q);
                break;
            case 4:
                // Dinamik belleği serbest bırakır ve programı kapatır
                freeQueue(&q);
                printf("[BİLGİ] Dinamik bellek (RAM) temizleniyor...\n");
                printf("[BİLGİ] Sistem güvenli bir şekilde kapatıldı.\n");
                break;
            default:
                printf("[HATA] Geçersiz seçim! Lütfen tekrar deneyiniz.\n");
                break;
        }
    }

    return 0;
}