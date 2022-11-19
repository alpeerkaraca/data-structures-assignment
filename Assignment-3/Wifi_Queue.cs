using System.Collections;

class Wifi_Queue
{
    public static void Main()
    {
        //Bu örnek WIFI-5 ve öncesi nesiller için geçerlidir. WIFI-6 ile paketler senkron şekilde işlendiğinden kuyruk yapısına olan benzerliği de azalmıştır.
        Queue wifi_queue = new();
        while (true)
        {
            int m_select = Menu();
            switch (m_select)
            {
                case 1:
                    Console.Write("İşlem Adı: ");
                    wifi_queue.Enqueue(Console.ReadLine());
                    Console.WriteLine("Devam Etmek İçin Herhangi Bir Tuşa Basınız");
                    Console.ReadKey();

                    break;
                case 2:
                    Console.WriteLine($"Sırada Bekleyen İşlem Sayısı: {wifi_queue.Count}");
                    Console.WriteLine("Devam Etmek İçin Herhangi Bir Tuşa Basınız");
                    Console.ReadKey();
                    break;
                case 3:
                    if (wifi_queue.Count > 0)
                        Console.WriteLine($"Sıradaki İşlem: {wifi_queue.Peek()}");
                    else
                        Console.WriteLine("Sırada İşlem Yok.");
                    Console.WriteLine("Devam Etmek İçin Herhangi Bir Tuşa Basınız");
                    Console.ReadKey();
                    break;
                case 4:
                    if (wifi_queue.Count > 0)
                        Console.WriteLine($"Tamamlanan İşlem: {wifi_queue.Dequeue()}");
                    else
                        Console.WriteLine("Sırada İşlem Yok.");
                    Console.WriteLine("Devam Etmek İçin Herhangi Bir Tuşa Basınız");
                    Console.ReadKey();
                    break;
                case 5:
                    if (wifi_queue.Count > 0)
                    {
                        foreach (object obj in wifi_queue)
                            Console.WriteLine(obj.ToString());
                    }
                    else
                        Console.WriteLine("Sırada İşlem Yok.");
                    Console.WriteLine("Devam Etmek İçin Herhangi Bir Tuşa Basınız");
                    Console.ReadKey();
                    break;
                case 6:
                    wifi_queue.Clear();
                    Console.WriteLine("Tüm İşlemler Tamamlandı !");
                    Console.WriteLine("Devam Etmek İçin Herhangi Bir Tuşa Basınız");
                    Console.ReadKey();
                    break;
                case 7:
                    Console.Write("İşlem Adı: ");
                    if (wifi_queue.Contains(Console.ReadLine()))
                        Console.WriteLine("Bu İşlem Sıradadır");
                    else
                        Console.WriteLine("Sırada Böyle Bir İşlem Bulunamadı");
                    Console.WriteLine("Devam Etmek İçin Herhangi Bir Tuşa Basınız");
                    Console.ReadKey();
                    break;
                case 8:
                    System.Environment.Exit(1);
                    Console.Clear();
                    break;
                default:
                    Console.WriteLine("Bu Seçenek Mevcut Değil");
                    Console.WriteLine("Devam Etmek İçin Herhangi Bir Tuşa Basınız");
                    Console.ReadKey();
                    break;
            }
        }
    }

    private static int Menu()
    {
        Console.Clear();
        Console.WriteLine(
            "|--------------------------------------------------------------------------------------------------|"
        );
        Console.WriteLine(
            "|1)Router'e İşlem Gönder\t2)Bekleyen İşlem Sayısını Görüntüle\t3)Sıradaki İşlemi Görüntüle|"
        );
        Console.WriteLine(
            "|4)Sıradaki İşlemi Tamamla\t5)Sıradaki İşlemeri Görüntüle\t\t6)Bütün İşlemleri Tamamla  |"
        );
        Console.WriteLine("|7)İşlem Araması Yap \t\t\t\t\t\t\t8)Çıkış Yap\t\t   |");
        Console.WriteLine(
            "|--------------------------------------------------------------------------------------------------|"
        );
        Console.Write("İşlem: ");
        return Convert.ToInt32(Console.ReadLine());
    }
}