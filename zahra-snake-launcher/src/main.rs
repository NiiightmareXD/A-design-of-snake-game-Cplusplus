#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]

use eframe::egui::{self, gui_zoom::zoom_in, Layout};
use rodio::OutputStream;
use std::{
    fs::{self, File},
    io::BufReader,
    process::Command,
};

use tempfile::TempDir;

fn write_files(tmpdir: &TempDir) {
    fs::write(
        tmpdir
            .path()
            .join("Noisestorm-Crab-Rave-Monstercat-Release.ogg"),
        include_bytes!("../../ZahraSnake/Music/Noisestorm-Crab-Rave-Monstercat-Release.ogg"),
    )
    .unwrap();

    fs::write(
        tmpdir.path().join("openal32.dll"),
        include_bytes!("../../ZahraSnake/SFML/bin/openal32.dll"),
    )
    .unwrap();

    fs::write(
        tmpdir.path().join("sfml-audio-2.dll"),
        include_bytes!("../../ZahraSnake/SFML/bin/sfml-audio-2.dll"),
    )
    .unwrap();

    fs::write(
        tmpdir.path().join("sfml-graphics-2.dll"),
        include_bytes!("../../ZahraSnake/SFML/bin/sfml-graphics-2.dll"),
    )
    .unwrap();

    fs::write(
        tmpdir.path().join("openal32.dll"),
        include_bytes!("../../ZahraSnake/SFML/bin/openal32.dll"),
    )
    .unwrap();

    fs::write(
        tmpdir.path().join("sfml-network-2.dll"),
        include_bytes!("../../ZahraSnake/SFML/bin/sfml-network-2.dll"),
    )
    .unwrap();

    fs::write(
        tmpdir.path().join("sfml-system-2.dll"),
        include_bytes!("../../ZahraSnake/SFML/bin/sfml-system-2.dll"),
    )
    .unwrap();

    fs::write(
        tmpdir.path().join("sfml-window-2.dll"),
        include_bytes!("../../ZahraSnake/SFML/bin/sfml-window-2.dll"),
    )
    .unwrap();

    fs::write(
        tmpdir.path().join("ZahraSnake.exe"),
        include_bytes!("../../x64/Release/ZahraSnake.exe"),
    )
    .unwrap();
}

fn main() -> Result<(), eframe::Error> {
    let options = eframe::NativeOptions {
        initial_window_size: Some(egui::vec2(600.0, 300.0)),
        ..Default::default()
    };
    eframe::run_native(
        "Zahra Snake",
        options,
        Box::new(|_cc| Box::<MyApp>::default()),
    )
}

struct MyApp {
    name: String,
    difficulty: u32,
    score: u32,
}

impl Default for MyApp {
    fn default() -> Self {
        Self {
            name: "Zahra".to_string(),
            difficulty: 2,
            score: 0,
        }
    }
}

impl eframe::App for MyApp {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        if ctx.pixels_per_point() < 1.5 {
            zoom_in(ctx);
            zoom_in(ctx);
            zoom_in(ctx);
            zoom_in(ctx);
            zoom_in(ctx);
        }
        egui::CentralPanel::default().show(ctx, |ui| {
            ui.vertical_centered(|ui| {
                ui.with_layout(
                    Layout::top_down_justified(eframe::emath::Align::Center),
                    |ui| {
                        ui.heading("Zahra Snake");
                        ui.horizontal(|ui| {
                            let name_label = ui.label("Your name: ");
                            ui.text_edit_singleline(&mut self.name)
                                .labelled_by(name_label.id);
                        });
                        ui.add(egui::Slider::new(&mut self.difficulty, 1..=5).text("Difficulty"));
                        if ui.button("Start Game").clicked() {
                            let tmpdir: TempDir = tempfile::tempdir().unwrap();
                            write_files(&tmpdir);
                            let (_stream, stream_handle) = OutputStream::try_default().unwrap();
                            let file = BufReader::new(
                                File::open(
                                    tmpdir
                                        .path()
                                        .join("Noisestorm-Crab-Rave-Monstercat-Release.ogg"),
                                )
                                .unwrap(),
                            );
                            let sink = stream_handle.play_once(file).unwrap();
                            sink.set_volume(0.369);
                            self.score = Command::new(tmpdir.path().join("ZahraSnake.exe"))
                                .arg((self.difficulty * 10 / 2).to_string())
                                .current_dir(tmpdir.path())
                                .spawn()
                                .unwrap()
                                .wait()
                                .unwrap()
                                .code()
                                .unwrap() as u32;
                        }
                        ui.label(format!("Highscore: {}", self.score));
                    },
                );
            });
        });
    }
}
