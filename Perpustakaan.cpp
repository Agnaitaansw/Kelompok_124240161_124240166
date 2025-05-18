#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

// Struct Buku
struct Buku {
    int id_buku;
    string Judul;
    int thn_terbit;
    string pengarang;
    bool tersedia = true; 
    Buku* next;
};
// Struct anggota
struct anggota {
    int idAnggota;
    string namaAnggota;
    anggota* next;
};

// Struct Peminjaman
struct peminjaman {
    string namaAnggota;
    int idBuku;
    string judulBuku;
    peminjaman* next;
};

// Pointer
Buku* headBuku = nullptr;
peminjaman* front = nullptr;
peminjaman* rear = nullptr;

// Fungsi untuk menambah data buku
void tambahBuku(int id_Buku, string Judul, int thn_terbit, string pengarang) {
    Buku* baru = new Buku{id_Buku, Judul, thn_terbit, pengarang, true, nullptr};
    if (!headBuku)
        headBuku = baru;
    else {
        Buku* temp = headBuku;
        while (temp->next)
            temp = temp->next;
        temp->next = baru;
    }
}

// Fungsi untuk mengurutkan data buku berdasarkan tahun terbit
void mengurutkanBuku() {
    if (!headBuku || !headBuku->next) return;

    for (Buku* i = headBuku; i->next; i = i->next) {
        for (Buku* j = i->next; j; j = j->next) {
            if (i->thn_terbit > j->thn_terbit) {
                swap(i->id_buku, j->id_buku);
                swap(i->Judul, j->Judul);
                swap(i->thn_terbit, j->thn_terbit);
                swap(i->pengarang, j->pengarang);
                swap(i->tersedia, j->tersedia);
            }
        }
    }
}

// Fungsi untuk menampilkan daftar buku
void tampilkanBuku() {
    Buku* temp = headBuku;
    if (!temp) {
        cout << "\nTidak ada buku.\n";
        return;
    }

    cout << "-------------------------------------------------------------\n";
    cout << "| Id_buku |    Judul Buku     | Tahun |    Pengarang    | Status |\n";
    cout << "-------------------------------------------------------------\n";

    while (temp) {
        cout << "| " << setw(7) << temp->id_buku
             << " | " << setw(18) << temp->Judul
             << " | " << setw(5) << temp->thn_terbit
             << " | " << setw(15) << temp->pengarang
             << " | " << (temp->tersedia ? "Tersedia" : "Dipinjam") << " |\n";
        temp = temp->next;
    }
    cout << "-------------------------------------------------------------\n";
}

// Fungsi untuk mencari buku berdasarkan ID
Buku* cariBuku(int idBuku) {
    Buku* temp = headBuku;
    while (temp) {
        if (temp->id_buku == idBuku)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}
// Fungsi untuk mencari buku berdasarkan ID
Buku* cariBuku(int idBuku) {
    Buku* temp = headBuku;
    while (temp) {
        if (temp->id_buku == idBuku)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}

// Fungsi peminjaman (queue)
void antriPeminjaman(string namaAnggota, int idBuku) {
    Buku* buku = cariBuku(idBuku);
    if (!buku) {
        cout << "Buku tidak ditemukan.\n";
        return;
    }
    if (!buku->tersedia) {
        cout << "Buku sedang dipinjam.\n";
        return;
    }

    peminjaman* baru = new peminjaman{namaAnggota, idBuku, buku->Judul, nullptr};
    if (!rear) front = rear = baru;
    else {
        rear->next = baru;
        rear = baru;
    }
    buku->tersedia = false;
    cout << "\nBuku '" << buku->Judul << "' berhasil dipinjam oleh " << namaAnggota << ".\n";
}

// Simpan data buku ke file
void simpanKeFile() {
    ofstream file("data_buku.txt");
    Buku* temp = headBuku;
    while (temp) {
        file << temp->id_buku << ";" << temp->Judul << ";" << temp->pengarang << ";" << temp->thn_terbit << ";" << temp->tersedia << endl;
        temp = temp->next;
    }
    file.close();
}

// Fungsi baca dari file
void bacaDariFile() {
    ifstream file("data_buku.txt");
    if (!file.is_open()) {
        cout << "Gagal membuka file.\n";
        return;
    }

    int id, tahun;
    string judul, pengarang;
    bool status;
    while (getline(file, judul, ';')) {
        file >> id;
        file.ignore();
        getline(file, judul, ';');
        getline(file, pengarang, ';');
        file >> tahun;
        file.ignore();
        file >> status;
        file.ignore();

        Buku* baru = new Buku{id, judul, tahun, pengarang, status, nullptr};
        if (!headBuku)
            headBuku = baru;
        else {
            Buku* temp = headBuku;
            while (temp->next)
                temp = temp->next;
            temp->next = baru;
        }
    }
    file.close();
    cout << "Data berhasil dibaca dari file.\n";
}

// Fungsi pengembalian buku
void kembalikanBuku(string namaAnggota, int idBuku) {
    peminjaman* prev = nullptr;
    peminjaman* temp = front;

    while (temp) {
        if (temp->namaAnggota == namaAnggota && temp->idBuku == idBuku) {
            if (temp == front) {
                front = front->next;
                if (temp == rear) rear = nullptr;
            } else {
                prev->next = temp->next;
                if (temp == rear) rear = prev;
            }    
            Buku* buku = cariBuku(idBuku);
            if (buku) buku->tersedia = true;

            cout << "\nBuku '" << temp->judulBuku << "' telah dikembalikan oleh " << namaAnggota << ".\n";
            delete temp;
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    cout << "\nData peminjaman tidak ditemukan untuk pengembalian.\n";
}

// Fungsi utama
int main() {
    int pilihan;

    do {
        cout << "\n======================\n";
        cout << "   Menu Perpustakaan\n";
        cout << "======================\n";
        cout << "1. Tambah Buku\n";
        cout << "2. Urutkan Buku\n";
        cout << "3. Tampilkan Buku\n";
        cout << "4. Cari Buku\n";
        cout << "5. Peminjaman\n";
        cout << "6. Tampilkan Antrian\n";
        cout << "7. Simpan ke File\n";
        cout << "8. Baca dari File\n";
        cout << "9. Pengembalian Buku\n";
        cout << "0. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: {
                int id, tahun;
                string judul, pengarang;
                cout << "Masukkan ID Buku: ";
                cin >> id;
                cin.ignore();
                cout << "Masukkan Judul Buku: ";
                getline(cin, judul);
                cout << "Masukkan Pengarang: ";
                getline(cin, pengarang);
                cout << "Masukkan Tahun Terbit: ";
                cin >> tahun;

                tambahBuku(id, judul, tahun, pengarang);
                break;
            }

            case 2:
                mengurutkanBuku();
                cout << "Data buku berhasil diurutkan.\n";
                break;

            case 3:
                tampilkanBuku();
                break;

            case 4: {
                int id;
                cout << "Masukkan ID Buku: ";
                cin >> id;
                Buku* buku = cariBuku(id);
                if (buku) {
                    cout << "Buku ditemukan: " << buku->Judul << ", Pengarang: " << buku->pengarang << endl;
                } else {
                    cout << "Buku tidak ditemukan.\n";
                }
                break;
            }

            case 5: {
                string namaAnggota;
                int idBuku;
                cout << "Masukkan Nama Anggota: ";
                cin.ignore();
                getline(cin, namaAnggota);
                cout << "Masukkan ID Buku: ";
                cin >> idBuku;

                antriPeminjaman(namaAnggota, idBuku);
                break;
            }

            case 6:
                if (front) {
                    cout << "Antrian Peminjaman:\n";
                    peminjaman* temp = front;
                    while (temp) {
                        cout << "Nama: " << temp->namaAnggota << ", ID Buku: " << temp->idBuku << ", Judul: " << temp->judulBuku << endl;
                        temp = temp->next;
                    }
                } else {
                    cout << "Tidak ada antrian peminjaman.\n";
                }
                break;

            case 7:
                simpanKeFile();
                cout << "Data buku berhasil disimpan ke file.\n";
                break;

            case 8:
                bacaDariFile();
                break;

            case 9; {
                string nama;
                int id;
                cout << "Masukkan nama anggota: ";
                cin.ignore();
                getline(cin, nama);
                cout << "Masukkan ID buku yang dikembalikan: ";
                cin >> id;
                kembalikanBuku(nama, id);
                break;
            }

            case 0:
                cout << "Keluar dari program.\n";
                break;

            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }

    } while (pilihan != 0);

    return 0;
}
