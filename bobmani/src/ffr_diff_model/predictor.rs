use std::collections::HashMap;
use crate::ffr_diff_model::features::{HorizontalDensity, VerticalDensity, StreamDetector, PatternDetector, OrderedFloat};
use crate::ffr_diff_model::preprocessor::SMChartPreprocessor;
use std::collections::BTreeMap;

pub struct DifficultyPredictor {
    preprocessor: SMChartPreprocessor,
    horizontal_density: HorizontalDensity,
    vertical_density: VerticalDensity,
    stream_detector: StreamDetector,
    pattern_detector: PatternDetector,
}

impl DifficultyPredictor {
    pub fn new() -> Self {
        Self {
            preprocessor: SMChartPreprocessor::new(3),
            horizontal_density: HorizontalDensity::new(3.0),
            vertical_density: VerticalDensity::new(3.0),
            stream_detector: StreamDetector::new(0.25),
            pattern_detector: PatternDetector::new(0.1),
        }
    }

    pub fn predict(&self, sm_path: &str) -> Vec<HashMap<String, f64>> {
        let mut batch_predictions = Vec::new();

        let preprocessed_charts = self.preprocessor.preprocess(sm_path);

        for chart_data in preprocessed_charts {
            let features = self.extract_features(&chart_data.chart);
            // In the future: route features to the loaded ML model and append result.
            batch_predictions.push(features);
        }

        batch_predictions
    }

    fn extract_features(&self, chart: &BTreeMap<OrderedFloat, String>) -> HashMap<String, f64> {
        let mut features = HashMap::new();

        features.extend(self.horizontal_density.compute(chart));
        features.extend(self.vertical_density.compute(chart));
        features.extend(self.stream_detector.compute(chart));
        features.extend(self.pattern_detector.compute(chart));

        features
    }
}
