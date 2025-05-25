#include <iostream>
#include <cstring>
using namespace std;

struct mahasiswa {
    int nim;
    char nama[100];
    mahasiswa *kiri;
    mahasiswa *kanan;

    mahasiswa(int val, const char* namaa) {
        nim = val;
        strcpy(nama, namaa);
        kiri = kanan = nullptr;
    }
};

void sisip(mahasiswa *&akar, int nim, const char* nama) {
    if (akar == nullptr) {
        akar = new mahasiswa(nim, nama);
        return;
    }

    mahasiswa *bntr = akar;
    while (true) {
        if (nim < bntr->nim) {
            if (bntr->kiri == nullptr) {
                bntr->kiri = new mahasiswa(nim, nama);
                return;
            }
            bntr = bntr->kiri;
        } else {
            if (bntr->kanan == nullptr) {
                bntr->kanan = new mahasiswa(nim, nama);
                return;
            }
            bntr = bntr->kanan;
        }
    }
}

void inorder(mahasiswa *akar) {
    if (akar != nullptr) {
        inorder(akar->kiri);
        cout << "NIM: " << akar->nim << ", Nama: " << akar->nama << endl;
        inorder(akar->kanan);
    }
}

void hapus(mahasiswa *&akar, int target) {
    if (akar == nullptr){
        cout << "tree tidak ada";
        return;}

    if (target < akar->nim) {
        hapus(akar->kiri, target);
    } else if (target > akar->nim) {
        hapus(akar->kanan, target);
    } else {
        mahasiswa *temp = akar; 
        if (akar->kiri == nullptr) {
            akar = akar->kanan;
        } else if (akar->kanan == nullptr) {
            akar = akar->kiri;
        } else {
            mahasiswa *dlt = akar->kanan;
            while (dlt->kiri != nullptr) {
                dlt = dlt->kiri;
            }
            akar->nim = dlt->nim;
            strcpy(akar->nama, dlt->nama);
            hapus(akar->kanan, dlt->nim);
            return;
        }
        delete temp;
    }
}

void cari(mahasiswa *akar, int target) {
    mahasiswa *bntr = akar;
    while (bntr) {
        if (bntr->nim == target) {
            cout << "Data ditemukan: NIM = " << bntr->nim << ", Nama = " << bntr->nama << endl;
            return;
        }
        bntr = (target < bntr->nim) ? bntr->kiri : bntr->kanan;
    }
    cout << "NIM " << target << " tidak ditemukan." << endl;
}

void muatDariFile(FILE *ptr, mahasiswa *&akar) {
    int nim;
    char nama[100];
    while (fread(&nim, sizeof(int), 1, ptr) == 1) {
    if (fread(nama, sizeof(nama), 1, ptr) != 1) {
        cout << "Gagal membaca nama." << endl;
        break;
    }
    sisip(akar, nim, nama);
}
}

void baca(FILE *ptr, mahasiswa *akar) {
    if (akar != nullptr) {
        fwrite(&akar->nim, sizeof(int), 1, ptr);
        fwrite(akar->nama, sizeof(akar->nama), 1, ptr);
        baca(ptr, akar->kiri);
        baca(ptr, akar->kanan);
    }
}

void simpankefile(mahasiswa *akar) {
    FILE *ptr = fopen("data_mhs.dat", "wb");
    if (ptr == NULL) {
        cout << "Gagal membuka file untuk menyimpan.\n";
        return;
    }

    baca(ptr, akar);
    fclose(ptr);
    cout << "Data mahasiswa berhasil disimpan ke file.\n";
}

int main() {
    mahasiswa *akar = nullptr;
    int jumlah, pilih;

    FILE *ptr = fopen("data_mhs.dat", "rb");
    if (ptr != NULL) {
    muatDariFile(ptr, akar);
    fclose(ptr);} 
    do
    {
        cout<< "pilih menu" << endl;
        cout<< "1. input" << endl;
        cout<< "2. cari" << endl;
        cout<< "3. cetak" << endl;
        cout<< "4. hapus" << endl;
        cout<< "5. keluar" << endl;
        cout << "pilih menu nomor berapa: ";
        cin >> pilih;

        switch (pilih)
        {
        case 1:
            cout << "Masukkan jumlah mahasiswa: ";
            cin >> jumlah;
            cin.ignore();

            for (int i = 0; i < jumlah; i++) {
            int nim;
            char nama[100];
            cout << endl << "Mahasiswa ke-" << (i + 1) << endl;
            cout << "Masukkan NIM: ";
            cin >> nim;
            cin.ignore();
            cout << "Masukkan Nama: ";
            cin.getline(nama, 100);
            sisip(akar, nim, nama);}
            simpankefile(akar);
            break;
        case 2:
            int nimCari;
            cout << endl << "Masukkan NIM yang ingin dicari: ";
            cin >> nimCari;
            cari(akar, nimCari);
            break;
        case 3:
            cout << endl << "Data Mahasiswa (Inorder):" << endl;
            inorder(akar);
            break;
        case 4:
            int nimHapus;
            cout << "Masukkan NIM yang ingin dihapus: ";
            cin >> nimHapus;
            hapus(akar, nimHapus);
            simpankefile(akar);
            cout << "Data dengan NIM " << nimHapus << " telah dihapus (jika ada)." << endl;
            break;
        case 5:
            cout << "keluar dari Program";
            break;
        default:
            cout << "angka tidak sesuai dengan menu";
            break;
        }
        
    } while (pilih != 5);
}
