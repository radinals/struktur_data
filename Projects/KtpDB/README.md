# KtpDB
### Implementasi Database Data KTP Sederhana.

Data disimpan didalam array yang akan berubah ukurannya tergantung
berapa data yang harus disimpan.

Pencarian dilakukan secara linier dan menggunakan metode sequential.

Deleting dilakukan dengan memindahkan data tersebut ke ujung array, dan
me-dekremen counter elemen array, hingga akan terlihat 'terhapus'.

Input di proses secara token, atau perkata. Hingga jika dikemudian hari
perlu ditambah perintah baru atau kombinasi perintah yang baru akan dengan
mudah dilakukan.

### Build:

Hanya memerlukan compiler c++ yang support >= c++11 (versi yang sangat umum).

dan build process di automasi dengan GNU-Make.

```sh
make
```

### Cara Pakai:

Menggunakan interface command prompt sederhana. Berikut
adalah beberapa perintah yang diterima.

- Printing

    LIST                    -> Tampilkan Semua Data

- Pencarian

    SEARCH #12              -> Tampilkan data di index 12.

    SEARCH ALL NAMA budi    -> Cari SEMUA data yang memiliki NAMA 'budi' dan tampilkan.

    SEARCH FIRST NAMA budi  -> Tampilkan data PERTAMA yang ditemukan memiliki NAMA budi.

- Deleting

    DELETE #12             -> hapus data di index 12.

    DELETE ALL NAMA budi   -> hapus SEMUA data yang memiliki NAMA budi

    DELETE FIRST NAMA budi -> hapus data PERTAMA yang ditemukan memiliki NAMA budi.

- EDIT

    EDIT #12               -> re-input data index 12.

    EDIT NAMA #12          -> edit data NAMA di index 12

- ADDING

    ADD                    -> (input data baru)

### TODO

* [ ] Save/Read ke/dari file
* [ ] Input Checking yang lebih efisien.
