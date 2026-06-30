use std::f32;

/// A simple 1D convolution mimicking numpy.convolve(..., mode='same')
pub fn convolve_same(data: &[f32], kernel: &[f32]) -> Vec<f32> {
    let mut out = vec![0.0; data.len()];
    let k_len = kernel.len();
    if k_len == 0 {
        return out;
    }

    let k_half = k_len / 2;

    for i in 0..data.len() {
        let mut sum = 0.0;
        for j in 0..k_len {
            // Index in data corresponding to kernel position j
            let data_idx = i as isize + j as isize - k_half as isize;

            if data_idx >= 0 && data_idx < data.len() as isize {
                sum += data[data_idx as usize] * kernel[j];
            }
        }
        out[i] = sum;
    }

    out
}

/// Generates a Hamming window of size N
pub fn hamming_window(n: usize) -> Vec<f32> {
    if n == 0 {
        return vec![];
    }
    if n == 1 {
        return vec![1.0];
    }

    let mut win = Vec::with_capacity(n);
    let alpha = 0.54;
    let beta = 0.46;
    let denominator = (n - 1) as f32;

    for i in 0..n {
        let val = alpha - beta * (2.0 * f32::consts::PI * (i as f32) / denominator).cos();
        win.push(val);
    }
    win
}

/// Finds local maxima (peaks) mimicking scipy.signal.argrelextrema(..., np.greater_equal, order=1)
pub fn find_peaks(onset_salience: &[f32]) -> Vec<usize> {
    if onset_salience.is_empty() {
        return vec![];
    }

    let hamming = hamming_window(5);
    let smoothed = convolve_same(onset_salience, &hamming);

    let mut peaks = Vec::new();
    let n = smoothed.len();

    if n == 1 {
        peaks.push(0);
        return peaks;
    }

    for i in 0..n {
        let current = smoothed[i];

        let left_ok = if i == 0 { true } else { current >= smoothed[i - 1] };
        let right_ok = if i == n - 1 { true } else { current >= smoothed[i + 1] };

        if left_ok && right_ok {
            peaks.push(i);
        }
    }

    peaks
}

/// Returns peaks above a specific threshold
pub fn threshold_peaks(onset_salience: &[f32], peaks: &[usize], threshold: f32) -> Vec<usize> {
    peaks.iter()
        .copied()
        .filter(|&i| onset_salience[i] >= threshold)
        .collect()
}
