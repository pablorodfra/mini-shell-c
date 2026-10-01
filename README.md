# Mini Shell en C

Proyecto de iniciación a programación de sistemas: implementar un intérprete de comandos (shell) básico en C, similar en espíritu a `bash` o `sh` pero muy simplificado.

## Objetivo

Construir un programa que:
1. Muestre un prompt.
2. Lea una línea de comando escrita por el usuario.
3. La interprete y ejecute.
4. Repita el ciclo hasta que el usuario salga.

Esto te obliga a trabajar directamente con la interfaz que el sistema operativo expone a los programas: procesos, ejecución de binarios y gestión de su ciclo de vida.

## Especificaciones funcionales

### Fase 1 — Bucle básico (REPL)

- [ ] Mostrar un prompt (ej. `myshell> `).
- [ ] Leer una línea de texto desde stdin.
- [ ] Repetir el ciclo indefinidamente.
- [ ] Salir limpiamente con el comando `exit`.

### Fase 2 — Parsing de comandos

- [ ] Separar la línea leída en el comando y sus argumentos (tokenizar por espacios).
- [ ] Guardar los tokens en un array de strings terminado en `NULL` (formato que espera `execvp`).
- [ ] Manejar líneas vacías sin fallar.

### Fase 3 — Ejecución de comandos externos

- [ ] Usar `fork()` para crear un proceso hijo.
- [ ] En el proceso hijo, usar `execvp()` para reemplazar su imagen de memoria por el programa solicitado (ej. `ls`, `pwd`, `cat`).
- [ ] En el proceso padre, usar `wait()` o `waitpid()` para esperar a que el hijo termine antes de mostrar el siguiente prompt.
- [ ] Manejar el caso de comando no encontrado (mensaje de error, no crash).

### Fase 4 — Comandos internos (built-ins)

Estos comandos deben ejecutarse en el propio proceso del shell, sin `fork()`, porque cambian el estado del propio shell:

- [ ] `cd <ruta>` — cambia el directorio de trabajo (`chdir()`).
- [ ] `exit` — termina el shell.
- [ ] `help` (opcional) — muestra los comandos disponibles.

### Fase 5 — Mejoras (opcional, si quieres seguir)

- [ ] Soporte de `&` para ejecutar procesos en segundo plano (no esperar con `wait`).
- [ ] Redirección de entrada/salida (`>`, `<`) usando `dup2()`.
- [ ] Pipes (`|`) entre dos comandos usando `pipe()`.
- [ ] Historial de comandos.

## Requisitos técnicos

- **Lenguaje:** C (estándar C11 o similar).
- **Plataforma:** Linux (usa llamadas POSIX, no funcionará igual en Windows sin WSL).
- **Compilador:** `gcc` o `clang`.
- **Sin librerías externas** — solo la librería estándar de C y las cabeceras POSIX (`unistd.h`, `sys/wait.h`, etc.).

## Funciones clave que vas a necesitar

| Función | Cabecera | Para qué sirve |
|---|---|---|
| `fgets()` | `stdio.h` | Leer la línea de entrada |
| `strtok()` | `string.h` | Tokenizar la línea en argumentos |
| `fork()` | `unistd.h` | Crear un proceso hijo |
| `execvp()` | `unistd.h` | Ejecutar un programa en el proceso actual |
| `waitpid()` | `sys/wait.h` | Esperar a que termine el proceso hijo |
| `chdir()` | `unistd.h` | Cambiar de directorio (para `cd`) |
| `getcwd()` | `unistd.h` | Obtener el directorio actual (útil para el prompt) |

## Estructura de archivos sugerida

```
myshell/
├── README.md
├── Makefile
└── src/
    └── main.c
```

Para empezar puedes tenerlo todo en un único `main.c`; separar en varios archivos (parsing, ejecución, built-ins) tiene sentido cuando el código crezca.

## Criterio de "funciona"

El proyecto se considera completo en su forma mínima (fases 1–4) cuando:
1. Puedes ejecutar comandos externos como `ls -la`, `pwd`, `echo hola` con argumentos.
2. `cd` cambia correctamente el directorio y afecta a los comandos siguientes.
3. Un comando inexistente (ej. `asdkjfh`) muestra un error sin cerrar el shell.
4. `exit` cierra el programa de forma limpia (sin fugas de procesos zombie).

## Notas

- Usa `strace ./myshell` mientras lo pruebas para ver exactamente qué syscalls dispara cada comando — es la mejor forma de conectar lo que escribes con lo que hace el sistema operativo por debajo.
- No te preocupes por manejar todos los casos raros de shells reales (comillas, variables de entorno, expansión de `*`, etc.) en la primera versión. Eso es refinamiento posterior, no el objetivo de aprendizaje inicial.