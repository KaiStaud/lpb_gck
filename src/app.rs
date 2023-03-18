#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")] // hide console window on Windows in release

use std::sync::mpsc::Receiver;
use eframe::{egui};
use egui_dock::{DockArea,Style, Tree};
use egui::plot::{Line, Plot, PlotPoints};

struct TabViewer {
    vec_y : Vec<i64>
}

impl egui_dock::TabViewer for TabViewer {
    type Tab = String;

    fn ui(&mut self, ui: &mut egui::Ui, tab: &mut Self::Tab) {
        ui.label(format!("Content of {tab}"));

            let position_request:PlotPoints = (0..self.vec_y.len()).map(|i| {
                let x = i as f64;
                let y = self.vec_y[i as usize] as f64;
                [x, y]
            }).collect();

            let line = Line::new(position_request);
            Plot::new("my_plot").view_aspect(2.0).show(ui, |plot_ui| plot_ui.line(line));
    }

    fn title(&mut self, tab: &mut Self::Tab) -> egui::WidgetText {
        (&*tab).into()
    }
}

pub struct TemplateApp {
    tree: Tree<String>,
    receiver: Receiver<i64>,
    pub vec_y : Vec<i64>
}

impl TemplateApp {
    pub fn  new(cc: &eframe::CreationContext<'_>,rx:Receiver<i64>) -> Self {
        let tree = Tree::new(vec!["Position Request".to_owned(), "Position Response".to_owned()]);
        let measurements_rx = rx;
        let measurements_y = vec![];//0,1,2,3,4,5,6,7,8,9,0,2,4,6,8,10,9,6,3,0];
        Self { tree,receiver:measurements_rx,vec_y:measurements_y }
    }
}

impl eframe::App for TemplateApp {
     /// Called each time the UI needs repainting, which may be many times per second.
    /// Put your widgets into a `SidePanel`, `TopPanel`, `CentralPanel`, `Window` or `Area`.
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        let value_or_error = self.receiver.recv();
        let v = value_or_error.unwrap();
        self.vec_y.push(v);
        println!("Received {}",v);
        //let mut measurements = self.vec_y.to_owned();
        DockArea::new(&mut self.tree)
            .style(Style::from_egui(ctx.style().as_ref()))
            .show(ctx, &mut TabViewer {vec_y:self.vec_y.to_owned()});
    }
}