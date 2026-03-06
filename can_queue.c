#include <stdio.h>
#include <stdlib.h>
#include "can_queue.h" // Struct tanımları ve prototipler dahil edilir 

// Kuyruğu başlatma ve dinamik bellek ayırma 
void initQueue(MesajKuyrugu *q, int kapasite) {
    q->kapasite = kapasite;
    // Dinamik dizi (pointer) ile bellekte alan tahsisi 
    q->mesajlar = (CAN_Mesaj*)malloc(q->kapasite * sizeof(CAN_Mesaj)); 
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

// 1. Sensörden Mesaj Üret (Enqueue) 
void enqueue(MesajKuyrugu *q) {
    // Sınır Durumu: Kuyruk Taşması (Queue Overflow) 
    if (q->count == q->kapasite) {
        printf("[HATA] CAN Bus hattı dolu! Kapasite (%d) aşıldı. Yeni mesaj eklenemez.\n", q->kapasite); // [cite: 66, 102]
        return;
    }

    // Dairesel kuyruk mantığı ile rear indeksini ilerletme
    q->rear = (q->rear + 1) % q->kapasite;

    // Kullanıcıdan mesaj ID'si, veri değeri ve sensör adını alma 
    printf("Sensör Adı: ");
    scanf("%s", q->mesajlar[q->rear].gonderen);
    printf("Mesaj ID: ");
    scanf("%d", &q->mesajlar[q->rear].mesaj_id);
    printf("Veri: ");
    scanf("%f", &q->mesajlar[q->rear].veri);

    // Bilgileri CAN_Mesaj haline getirip kuyruğa ekleme ve sayacı artırma 
    q->count++;
    printf("[BİLGİ] Mesaj kuyruğa eklendi. (Sıradaki mesaj sayısı: %d)\n", q->count); 
}

// 2. Bekleyen İlk Mesajı İşle (Dequeue) 
void dequeue(MesajKuyrugu *q) {
    // Sınır Durumu: Boş Kuyruk (Queue Underflow)
    if (q->count == 0) {
        printf("[BİLGİ]: İşlenecek yeni mesaj bulunmuyor.\n"); 
        return;
    }

    // front sırasındaki mesajı kuyruktan alma 
    CAN_Mesaj islenen = q->mesajlar[q->front];

    // Mesajın içeriğini ekrana yazdırma 
    printf("[İŞLENDİ] %s (ID: %d) -> Veri: %.2f\n", islenen.gonderen, islenen.mesaj_id, islenen.veri); // [cite: 57, 108]
    
    // front indeksini ilerletme ve kuyruktan çıkarma işlemini tamamlama 
    q->front = (q->front + 1) % q->kapasite;
    q->count--;
    
    printf("[BİLGİ] Kuyrukta kalan mesaj sayısı: %d\n", q->count); 
}

// 3. Bekleyen Mesajları Göster (Print Queue) 
void printQueue(MesajKuyrugu *q) {
    // Kuyruktaki anlık count sayısını yazdırma 
    printf("\n[BEKLEYEN MESAJLAR Toplam: %d]\n", q->count); 
    if (q->count == 0) {
        return;
    }

    // İşlenecek ilk elemandan (front) başlayarak en son eklenen elemana (rear) kadar dolaşan döngü 
    for (int i = 0; i < q->count; i++) {
        int index = (q->front + i) % q->kapasite;
        printf("%d. %s (ID: %d) Veri: %.2f\n", i + 1, q->mesajlar[index].gonderen, q->mesajlar[index].mesaj_id, q->mesajlar[index].veri); 
    }
}

// 4. Sistemi Kapat (Memory Free) [cite: 62]
void freeQueue(MesajKuyrugu *q) {
    // Dinamik olarak ayrılan belleği RAM'e iade etme 
    free(q->mesajlar);
}