Acest proiect prezintă proiectarea și realizarea unui dispenser automat de shot-uri de băuturi, realizat cu ajutorul unei plăci Arduino, senzori IR și un servo motor. Sistemul este conceput pentru a detecta automat paharele plasate în fața dispenserului și pentru a turna câte un shot fiecăruia, într-un mod organizat și complet automatizat.

Dispenserul utilizează patru senzori IR poziționați în zona de servire pentru a detecta prezența paharelor. Fiecare senzor corespunde unei poziții specifice în care poate fi așezat un pahar. Atunci când un senzor detectează un pahar, sistemul rotește mecanismul de turnare, controlat de un servo motor, către poziția respectivă și menține poziția timp de aproximativ 2 secunde, simulând turnarea unui shot.

Pentru a asigura o funcționare corectă atunci când sunt detectate mai multe pahare, sistemul folosește o logică de tip coadă (FIFO – First In, First Out). Astfel, paharele sunt servite în ordinea în care au fost detectate, oferind un comportament predictibil și organizat. În situația în care mai mulți senzori sunt activați simultan, dispenserul procesează pozițiile în ordinea lor naturală.

După ce toate paharele detectate au fost servite, servo motorul revine automat la poziția inițială, pregătind sistemul pentru următoarele detectări.

Scopul principal al proiectului a fost realizarea unui sistem interactiv și automat, care îmbină concepte din electronică, programare embedded și mecanică, într-o aplicație practică și distractivă. Proiectul demonstrează modul în care senzori simpli și un mecanism de rotație pot fi integrați pentru a crea un sistem automat capabil să reacționeze la mediul înconjurător și să execute sarcini într-o ordine logică.

<img width="437" height="455" alt="dispenser" src="https://github.com/user-attachments/assets/0b8127f8-27c2-48e8-91e3-8b97cfd59cba" />

![WhatsApp Image 2026-03-12 at 17 21 54](https://github.com/user-attachments/assets/9507932f-82ab-4682-b396-22127b1b7cf5)

![3](https://github.com/user-attachments/assets/b3606271-b98b-4a32-a3fb-ec724b23c394)
