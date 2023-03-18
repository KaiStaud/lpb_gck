#![warn(clippy::all, rust_2018_idioms)]
#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")] // hide console window on Windows in release
 use lpb_gck::TemplateApp;
 use std::thread;
 use std::sync::mpsc::{self, Receiver};
 use std::time::Duration;

// When compiling natively:
#[cfg(not(target_arch = "wasm32"))]
fn main() {

    let (tx, rx) = mpsc::channel();

    thread::spawn(move || {
        let vals = vec![0,1,2,3,4,5,6,7,8,9,0,2,4,6,8,10,9,6,3,0];

        for val in vals {
            tx.send(val).unwrap();
            thread::sleep(Duration::from_millis(250));
        }
    }); 

    // Log to stdout (if you run with `RUST_LOG=debug`).
    tracing_subscriber::fmt::init();
    let thread_join_handle = thread::spawn(move || {
        // some work here
    });
    // some work here
    let native_options = eframe::NativeOptions::default();
    eframe::run_native(
        "eframe template",
        native_options,
        Box::new(|cc| Box::new(TemplateApp::new(cc,rx))),
    );

    let _res = thread_join_handle.join();

}

// when compiling to web using trunk.
#[cfg(target_arch = "wasm32")]
fn main() {
    // Make sure panics are logged using `console.error`.
    console_error_panic_hook::set_once();

    // Redirect tracing to console.log and friends:
    tracing_wasm::set_as_global_default();

    let web_options = eframe::WebOptions::default();
    eframe::start_web(
        "the_canvas_id", // hardcode it
        web_options,
        Box::new(|cc| Box::new(eframe_template::TemplateApp::new(cc))),
    )
    .expect("failed to start eframe");
}
