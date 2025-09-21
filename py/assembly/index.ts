let WIDTH: i32 = 400;
let HEIGHT: i32 = 300;
let PIXELS: i32 = WIDTH * HEIGHT;
let BYTES: i32 = PIXELS * 4;

let framebuffer: Uint8Array | null = null;

let g_mouse_x: i32 = WIDTH / 2;
let g_mouse_y: i32 = HEIGHT / 2;
let g_radius: i32 = 50;
let g_color_r: u8 = 255;
let g_color_g: u8 = 0;
let g_color_b: u8 = 0;

export function set_canvas_size(width: i32, height: i32): void {
  if (width <= 0 || height <= 0) return;
  WIDTH = width;
  HEIGHT = height;
  PIXELS = WIDTH * HEIGHT;
  BYTES = PIXELS * 4;
  framebuffer = new Uint8Array(BYTES);
  g_mouse_x = WIDTH / 2;
  g_mouse_y = HEIGHT / 2;
}

export function get_width(): i32 { return WIDTH; }
export function get_height(): i32 { return HEIGHT; }

export function get_framebuffer(): usize {
  if (!framebuffer) {
    set_canvas_size(400, 300);
  }
  return changetype<usize>(framebuffer!);
}

export function set_mouse_position(x: i32, y: i32): void {
  g_mouse_x = x;
  g_mouse_y = y;
}

export function handle_key(key_code: i32): void {
  if (key_code == 38) { // Up
    g_radius += 5;
    if (g_radius > 150) g_radius = 150;
  } else if (key_code == 40) { // Down
    g_radius -= 5;
    if (g_radius < 10) g_radius = 10;
  } else if (key_code == 37) { // Left → Blue
    g_color_r = 0; g_color_g = 0; g_color_b = 255;
  } else if (key_code == 39) { // Right → Green
    g_color_r = 0; g_color_g = 255; g_color_b = 0;
  } else if (key_code == 32) { // Space → Red
    g_color_r = 255; g_color_g = 0; g_color_b = 0;
  }
}

export function render_frame(frame_count: i32): void {
  if (!framebuffer) return;

  for (let i = 0; i < BYTES; i++) framebuffer![i] = 0;

  for (let y = 0; y < HEIGHT; y++) {
    for (let x = 0; x < WIDTH; x++) {
      let dx = x - g_mouse_x;
      let dy = y - g_mouse_y;
      if (dx * dx + dy * dy <= g_radius * g_radius) {
        let idx = (y * WIDTH + x) * 4;
        framebuffer![idx + 0] = g_color_r;
        framebuffer![idx + 1] = g_color_g;
        framebuffer![idx + 2] = g_color_b;
        framebuffer![idx + 3] = 255;
      }
    }
  }
}