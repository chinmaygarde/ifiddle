
#include <stdio.h>

int main(int argc, char const* argv[]) {
  printf("Hello from WASM with %d args.\n", argc);
  return 0;
}

void __imported_wasi_snapshot_preview1_args_get() {
  __builtin_trap();
}
void __imported_wasi_snapshot_preview1_args_sizes_get() {
  __builtin_trap();
}
void __imported_wasi_snapshot_preview1_fd_close() {
  __builtin_trap();
}
void __imported_wasi_snapshot_preview1_fd_fdstat_get() {
  __builtin_trap();
}
void __imported_wasi_snapshot_preview1_fd_seek() {
  __builtin_trap();
}
void __imported_wasi_snapshot_preview1_fd_write() {
  __builtin_trap();
}
void __imported_wasi_snapshot_preview1_proc_exit() {
  __builtin_trap();
}
