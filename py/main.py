import sys
from PySide6.QtWidgets import QApplication, QWidget, QMainWindow
from PySide6.QtGui import QPainter, QImage, QKeyEvent, QMouseEvent
from PySide6.QtCore import QTimer, Qt

from wasmtime import Func, FuncType, Store, Module, Instance, ValType

def abort(module: str, file: str, line: int, col: int):
    print(f"Abort called at {file}:{line}:{col} in module {module}")

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("WASM Paint")
        self.resize(800, 600)

        self.store = Store()
        self.module = Module.from_file(self.store.engine, "./build/release.wat")
        abort_type = FuncType([
            ValType.i32(),  # module ptr
            ValType.i32(),  # file ptr
            ValType.i32(),  # line
            ValType.i32()   # col
        ], [])
        abort_func = Func(self.store, abort_type, abort)

        self.instance = Instance(self.store, self.module, [abort_func])

        exports = self.instance.exports(self.store)

        self.render_frame = exports["render_frame"]
        self.set_mouse_position = exports["set_mouse_position"]
        self.handle_key = exports["handle_key"]
        self.get_framebuffer = exports["get_framebuffer"]
        self.get_width = exports["get_width"]
        self.get_height = exports["get_height"]
        self.set_canvas_size = exports["set_canvas_size"]
        self.memory = exports["memory"]

        self.set_canvas_size(self.store, self.width(), self.height())

        self.frame_count = 0
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.update_frame)
        self.timer.start(33)

    def update_frame(self):
        self.render_frame(self.store, self.frame_count)
        self.frame_count += 1
        self.update()


    def resizeEvent(self, event):
        self.set_canvas_size(self.store, self.width(), self.height())
        super().resizeEvent(event)

    def paintEvent(self, event):
        painter = QPainter(self)
        w = self.get_width(self.store)
        h = self.get_height(self.store)
        fb_ptr = self.get_framebuffer(self.store)
        fb_bytes = self.memory.read(self.store, fb_ptr, w * h * 4)
        print(fb_bytes)
        qimg = QImage(fb_bytes, w, h, QImage.Format_RGBA8888)
        print(qimg)
        # painter.drawImage(0, 0, qimg)

    def mouseMoveEvent(self, event: QMouseEvent):
        if event.buttons() & Qt.LeftButton:
            x = event.pos().x()
            y = event.pos().y()
            w = self.get_width(self.store)
            h = self.get_height(self.store)
            x = max(0, min(x, w - 1))
            y = max(0, min(y, h - 1))
            self.set_mouse_position(self.store, x, y)
        super().mouseMoveEvent(event)

    def mousePressEvent(self, event):
        if event.button() == Qt.LeftButton:
            self.mouseMoveEvent(event)
        super().mousePressEvent(event)

    def keyPressEvent(self, event: QKeyEvent):
        key_map = {
            Qt.Key_Up: 38,
            Qt.Key_Down: 40,
            Qt.Key_Left: 37,
            Qt.Key_Right: 39,
            Qt.Key_Space: 32,
        }
        key = event.key()
        if key in key_map:
            self.handle_key(self.store, key_map[key])
        else:
            super().keyPressEvent(event)

def test():
    store = Store()
    module = Module(store.engine, """
    (module
        (func $hello (import "" "hello"))
        (func (export "run") (call $hello))
    )
    """)

    def say_hello():
        print("Hello from Python!")
    hello = Func(store, FuncType([], []), say_hello)

    instance = Instance(store, module, [hello])
    run = instance.exports(store)["run"]
    run(store)

if __name__ == "__main__":
    test()
    store = Store()
    module = Module(store.engine, """
(module
  (func $gcd (param i32 i32) (result i32)
    (local i32)
    block  ;; label = @1
      block  ;; label = @2
        local.get 0
        br_if 0 (;@2;)
        local.get 1
        local.set 2
        br 1 (;@1;)
      end
      loop  ;; label = @2
        local.get 1
        local.get 0
        local.tee 2
        i32.rem_u
        local.set 0
        local.get 2
        local.set 1
        local.get 0
        br_if 0 (;@2;)
      end
    end
    local.get 2
  )
  (export "gcd" (func $gcd))
)
""")
    instance = Instance(store, module, [])
    gcd = instance.exports(store)["gcd"]

    print("gcd(6, 27) = %d" % gcd(store, 6, 27))

    app = QApplication(sys.argv)
    widget = MainWindow()
    widget.show()
    sys.exit(app.exec())