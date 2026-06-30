/// Cleans a string by removing whitespace and replacing non-alphanumeric characters with underscores
pub fn ezname(x: &str) -> String {
    let stripped: String = x.split_whitespace().collect();

    let mut clean = String::with_capacity(stripped.len());
    for ch in stripped.chars() {
        if ch.is_alphanumeric() {
            clean.push(ch);
        } else {
            clean.push('_');
        }
    }
    clean
}
