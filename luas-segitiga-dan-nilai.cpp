#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <limits.h>
#include <stdio.h>
#include <termios.h>
#include <thread>
#include <unistd.h>

// ╔══════════════════════════════════════════════════╗
// ║                                                  ║
// ║                UTILITY FUNCTIONS                 ║
// ║                                                  ║
// ╚══════════════════════════════════════════════════╝

void print_selection() 
{
  printf("=========================================\n"
         "         MENU PILIHAN PROGRAM            \n"
         "=========================================\n"
         "  1. Menghitung Luas Segitiga            \n"
         "  2. Konversi Nilai menjadi Grade        \n"
         "  0. Keluar                              \n"
         "=========================================\n"
         "  Masukkan pilihan Anda [0-2] : ");
}

void print_container(const char *title, unsigned int total_char) 
{
  unsigned int total_hashtag = 2 + 8 + total_char;
  unsigned int safe = total_hashtag;

  while ((total_hashtag--) > 0) {
    putchar(35);
  }
  printf("\n");
  total_hashtag = safe;

  printf("%c    ", 35);
  printf("%.*s", total_char, title);
  printf("    %c \n", 35);

  while ((total_hashtag--) > 0) {
    putchar(35);
  }
  printf("\n \n");
}

void print_informasi_kesalahan_input() {
  std::system("clear");

  printf("Input tidak valid. Tolong input satu angka saja sesuai yang ada di menu pilihan! \n");

  for (unsigned int i = 3; i > 0; i--) {
    printf("\rMengulangi dalam %d...", i);
    std::fflush(stdout);
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

void baca_input(int *wadah) {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  scanf("%d", wadah);
}
// ══════════════════════════════════════════════════════════════════════════

// ╔══════════════════════════════════════════════════╗
// ║                                                  ║
// ║                  MAIN FUNCTIONS                  ║
// ║                                                  ║
// ╚══════════════════════════════════════════════════╝

void menghitung_luas_segitiga() {
  std::system("clear");

  const char *title = "MENGHITUNG LUAS SEGITIGA";
  print_container(title, 24);

  unsigned int alas = 0;
  unsigned int tinggi = 0;

  printf("Masukkan ukuran alas segitiga: ");
  fflush(stdout);
  scanf("%d", &alas);

  printf("Masukkan ukuran tinggi segitiga: ");
  fflush(stdout);
  scanf("%d", &tinggi);

  unsigned int hasil = (alas * tinggi) / 2;
  printf("\n");
  printf("Luas Segitiga adalah: %d \n \n", hasil);
}

void konversi_nilai_ke_grade()
{
  std::system("clear");

  const char  *title          = "KONVERSI NILAI KE GRADE";
  const int   total_karakter  = 23;
  print_container(title, total_karakter);
  
  unsigned int nilai = 0;

  printf("Masukkan nilai angka(0-100): "); fflush(stdout); scanf("%d", &nilai);

  printf("\n");

  unsigned int jumlah_spasi = 12;
  while ((jumlah_spasi--) > 0) putchar(32);

  if (nilai >= 90) {
      printf("%d = A", nilai);
  } else if (nilai >= 80) {
      printf("%d = B", nilai);
  } else if (nilai >= 70) {
      printf("%d = C", nilai);
  } else if (nilai >= 60) {
      printf("%d = D", nilai);
  } else {
      printf("%d = E", nilai);
  }

  printf("\n \n");
}

signed int determine_direction_of_choice(unsigned int selection) 
{
  signed int signal = 1;

  switch (selection) 
  {
    case 1:  menghitung_luas_segitiga(); break;
    case 2:  konversi_nilai_ke_grade (); break;
    case 0:  signal =  0;  break;
    default: signal = -1;  break;
  }

  return signal;
}

void continue_confirm() {
  printf("Tekan tombol apapun untuk lanjut... ");
  fflush(stdout);

  termios lama = {};
  termios baru = {};

  // Save pengaturan terminal saat ini
  tcgetattr(STDIN_FILENO, &lama);

  // Copy pengaturan terminal lama ke terminal baru
  // Habis itu ubah pengaturan terminal baru
  baru = lama;
  baru.c_lflag &= ~(ICANON | ECHO);

  // Langsung apply pengaturan terminal baru
  tcsetattr(STDIN_FILENO, TCSANOW, &baru);

  // Siapkan wadah
  char tombol;

  // Baca satu kunci tombol dari keyboard
  read(STDIN_FILENO, &tombol, 1);

  // Tampilkan kunci tombol yang tekan
  printf("%c \n \n", tombol);

  // Kembalikan terminal ke kondisi semula
  tcsetattr(STDIN_FILENO, TCSANOW, &lama);
}

int main() {
  while (true) {
    std::system("clear");

    unsigned int selection = 0;
    unsigned int exit_signal = 0;
    print_selection();
    if (scanf("%d", &selection) != 1 || (exit_signal = determine_direction_of_choice(selection)) == -1) {

      print_informasi_kesalahan_input();
      continue;

    } else if (exit_signal == 0) { break; }

    continue_confirm();
    continue;
  }

  std::system("clear");
  exit(EXIT_SUCCESS);
}
