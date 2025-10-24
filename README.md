# LRU Cache (C, lista doble enlazada + índice A..Z)

## Compilación:
```bash
# Linux / macOS / MSYS2:
make       
# o en Windows (MSYS/MinGW):
mingw32-make
```

El binario queda en `bin/lru` (o `bin/lru.exe`).
* Abrir ejecutable
```
./lru.exe
```
## Comandos:
```bash
lru create N #Crea una cache con N espacios 
lru add N #Agrega contenido al cache (A...Z)
lru get N #Usa un elemento ya existente en la cache
lru search N #Enseña la posicion en la cache
lru exit #Detener el programa y eliminar memoria
```
## Ejemplo interactivo:

```BASH
lru create 5
lru add A
lru add B
lru get A
lru search B
lru all
lru exit
```

## Pruebas:
```BASH
En linux
# requiere bash y diff:
make test

# En Windows (cmd):
tests\test.bat
```

## Diseño:
- Lista **doblemente enlazada** para orden de recencia (head=MRU, tail=LRU).
- Índice `Node *index[26]` para A..Z en O(1).
- `add`: si está → "used", si no y hay espacio → inserta al frente, si no → expulsa `tail`.
- `get`: mueve a frente si existe.
- `search`: posición 1..n (MRU..LRU) o -1.

## Mensajes:

- `Cache created with size N` Cuando se crea una nueva cache
- `Data X added to cache` Cuando se agrega un elemento
- `Data element X used` Cuando se usa un elemento ya existente
- `Data element X deleted` (cuando hay expulsión)
- `Cache contents: <MRU> - ... - <LRU>` Muestra contenido de la cache actual
- `Data element X not found` (en `get`) No encuentra elemento o no existe

## Documentacion (Doxyfile)
La Documentacion se generara en base al archivo Doxyfile , Descargue e instale Doxygen para poder verlo en Html (https://www.doxygen.nl/)
- Ejecutar en la raiz del proyecto:
```BASH
 doxygen Doxyfile
```
- Se generara en la carpeta **docs** una carpeta llamada **Doxyfile** , al ingresar debera buscar archivo **Index.html**
