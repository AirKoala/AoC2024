use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();

    let mut nums1: Vec<u32> = Vec::new();
    let mut nums2: Vec<u32> = Vec::new();

    for line in stdin.lock().lines() {
        if line.is_err() {
            break;
        }

        let line = line.unwrap();

        nums1.push(line[0..5].parse().unwrap());
        nums2.push(line[8..13].parse().unwrap());
    }

    nums1.sort();
    nums2.sort();

    // for i in 0..nums1.len() {
    //     println!("{}: {} {}", i, nums1[i], nums2[i]);
    // }

    let mut dist: i32 = 0;
    let mut similarity: u64 = 0;

    for i in 0..nums1.len() {
        dist += (nums1[i] as i32 - nums2[i] as i32).abs();

        let s: u32 = match nums2.binary_search(&nums1[i]) {
            Ok(j_some) => {
                let mut j = j_some + 1;
                while nums2[j - 1] == nums1[i] {
                    j -= 1;
                }

                let mut k = j_some - 1;
                while k < nums2.len() && nums2[k + 1] == nums1[i] {
                    k += 1;
                }

                (k - j + 1).try_into().unwrap()
            }
            Err(_) => 0_u32,
        };

        similarity += (s * nums1[i]) as u64;
    }

    println!("Distance: {}", dist);
    println!("Similarity: {}", similarity);
}
