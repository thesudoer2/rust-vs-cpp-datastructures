## Results

<table>
    <thead>
        <tr>
            <th>Benchmark name</th>
            <th>Measured property</th>
            <th>Rust</th>
            <th>C++</th>
            <th>Ratio</th>
            <th>Winner</th>
            <th>Benchmark description</th>
            <th>Comment on result</th>
        </tr>
    </thead>
        <tr>
            <td rowspan=2>deque_push</td>
            <td>time</td>
            <td>275ms</td>
            <td>386ms</td>
            <td>1.4x</td>
            <td>Rust</td>
            <td rowspan=2>100M push of u64 numbers in VecDeque and deque</td>
            <td rowspan=2></td>
        </tr>
        <tr>
            <td>memory</td>
            <td>802MB</td>
            <td>841MB</td>
            <td>1x</td>
            <td>Rust</td>
        </tr>
        <tr>
            <td rowspan=2>hashset</td>
            <td>time</td>
            <td>37.5ms</td>
            <td></td>
            <td>0x</td>
            <td>C++</td>
            <td rowspan=2>1M insert of random u64 numbers in HashSet and unordered_set</td>
            <td rowspan=2>Rust uses Swiss table for its HashSet implementation, so it is faster</td>
        </tr>
        <tr>
            <td>memory</td>
            <td>39.5MB</td>
            <td></td>
            <td>0x</td>
            <td>C++</td>
        </tr>
