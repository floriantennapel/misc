use std::io;
use std::collections::BTreeMap;

fn main() {
    let mut map: BTreeMap<i32, i32> = BTreeMap::new(); 

    // ignore first line
    let mut buf = String::new();
    io::stdin()
        .read_line(&mut buf)
        .unwrap();

    // insert all numbers
    buf = String::new();
    io::stdin()
        .read_line(&mut buf)
        .unwrap();

    buf.trim()
        .split_whitespace()
        .map(|d| d.parse::<i32>().unwrap())
        .for_each(|d| {
            map.entry(d)
                .and_modify(|c| *c += 1)
                .or_insert(1);
        });

    io::stdin()
        .lines()
        .map(|l| l.unwrap()
            .split_whitespace()
            .map(|d| d.parse::<i32>().unwrap())
            .collect::<Vec<i32>>())
        .for_each(|p| {
            let mut to_remove: Option<i32> = None;
            let res = if p[0] == 1 { 
                map.range_mut(p[1]+1..).next() 
            } else { 
                map.range_mut(..=p[1]).next_back()
            };
            match res {
                Some(entry) => {
                    println!("{}", entry.0);
                    *entry.1 -= 1;
                    if *entry.1 == 0 {
                        to_remove = Some(*entry.0);
                    }
                },
                None => println!("-1"),
            }
            if to_remove.is_some() {
                map.remove(&to_remove.unwrap());
            }
        });
}
