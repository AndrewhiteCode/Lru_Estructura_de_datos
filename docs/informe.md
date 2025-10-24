
# Informe — LRU Cache

## 1. Introducción
Implementamos una caché **Least Recently Used (LRU)** en C, con tiempo O(1) para `add` y `get` usando lista doblemente enlazada más un índice directo para claves A..Z.

## 2. Diseño y estructuras
- **Lista doblemente enlazada**: cabeza=MRU, cola=LRU.
- **Índice [26]**: mapea `A..Z` → `Node*`.
- Alternativas: lista simple (O(n)), cola FIFO (no reordena por uso), hash+lista (más genérico, pero no necesario aquí).

## 3. Operaciones
- `create N` (N>=5), `add X`, `get X`, `search X`, `all`, `exit`.
- `add`: si existe → "used"; si no y sin espacio → expulsa LRU (cola).
- `get`: si existe mueve a MRU.
- `search`: posición 1..n (MRU..LRU) o -1.

## 4. Complejidad
- `add`, `get`, `search` = O(1) amortizado; `all` = O(n).
- Memoria: O(capacidad + 26).

## 5. Gestión de memoria
- `lru_free` libera todos los nodos y estructura.
- Sin fugas en pruebas con `valgrind` (sugerido).

## 6. Pruebas
- Secuencia de comandos reproduce el flujo de ejemplo.
- Casos borde: `add` repetido, `get` inexistente, expulsión al llenar.
