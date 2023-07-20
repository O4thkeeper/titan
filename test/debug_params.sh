const_params="
  --db=./db \
  --wal_dir=./db \
  \
  --num=300000 \
  --key_size=20 \
  --value_size=100 \
  --compression_ratio=0.5 \
  --compression_type=none \
  \
  --block_size=$((64 * 1024)) \
  --cache_size=$((256 * 1024)) \
  --cache_numshardbits=6 \
  --cache_index_and_filter_blocks=1 \
  --pin_l0_filter_and_index_blocks_in_cache=1 \
  --bloom_bits=10 \
  \
  --num_levels=7 \
  --write_buffer_size=$((16 * 1024 * 1024)) \
  --level_compaction_dynamic_level_bytes=true \
  --max_write_buffer_number=5 \
  --target_file_size_base=$((8 * 1024 * 1024)) \
  --max_bytes_for_level_base=$((64 * 1024 * 1024)) \
  --max_bytes_for_level_multiplier=10 \
  \
  --max_background_jobs=6 \
  --titan_max_background_gc=6 \
  --open_files=40960 \
  --statistics=1 \
  --verify_checksum=1 \
  \
  --bytes_per_sync=$((1 * 1024 * 1024)) \
  --wal_bytes_per_sync=$((512 * 1024)) \
  \
  --use_titan=true \
  "

function run_bulkload {
  # This runs with a vector memtable and the WAL disabled to load faster. It is still crash safe and the
  # client can discover where to restart a load after a crash. I think this is a good way to load.

  # TITAN: The implementation of memtable is changed from vector to default skiplist. Because GC in titan need to get in memtable. Vector will cause poor performance.
  echo "Bulk loading $num_keys random keys"
  cmd="./titandb_bench --benchmarks=fillrandom \
       $const_params \
       --use_existing_db=0 \
       --disable_auto_compactions=1 \
       --disable_wal=true
       --sync=false \
       --titan_disable_background_gc=true \
       --threads=${num_threads} \
       --seed=$( date +%s ) \
       2>&1 | tee -a $output_dir/benchmark_bulkload_fillrandom.log"
  echo $cmd | tee $output_dir/benchmark_bulkload_fillrandom.log
  eval $cmd
  summarize_result $output_dir/benchmark_bulkload_fillrandom.log bulkload fillrandom
  echo "Compacting..."
  cmd="./titandb_bench --benchmarks=compact \
       --use_existing_db=1 \
       --disable_auto_compactions=1 \
       --sync=0 \
       $const_params \
       --threads=1 \
       2>&1 | tee -a $output_dir/benchmark_bulkload_compact.log"
  echo $cmd | tee $output_dir/benchmark_bulkload_compact.log
  eval $cmd
}



./titandb_bench --benchmarks=fillrandom \
       --db=./db \
         --wal_dir=./db \
         \
         --num=300000 \
         --key_size=20 \
         --value_size=100 \
         --compression_ratio=0.5 \
         --compression_type=none \
         \
         --block_size=$((64 * 1024)) \
         --cache_size=$((256 * 1024)) \
         --cache_numshardbits=6 \
         --cache_index_and_filter_blocks=1 \
         --pin_l0_filter_and_index_blocks_in_cache=1 \
         --bloom_bits=10 \
         \
         --num_levels=7 \
         --write_buffer_size=$((16 * 1024 * 1024)) \
         --level_compaction_dynamic_level_bytes=true \
         --max_write_buffer_number=5 \
         --target_file_size_base=$((8 * 1024 * 1024)) \
         --max_bytes_for_level_base=$((64 * 1024 * 1024)) \
         --max_bytes_for_level_multiplier=10 \
         \
         --max_background_jobs=6 \
         --titan_max_background_gc=6 \
         --open_files=40960 \
         --statistics=1 \
         --verify_checksum=1 \
         \
         --bytes_per_sync=$((1 * 1024 * 1024)) \
         --wal_bytes_per_sync=$((512 * 1024)) \
         \
         --use_titan=true \
       --use_existing_db=0 \
       --disable_auto_compactions=1 \
       --disable_wal=true
       --sync=false \
       --titan_disable_background_gc=true \
       --threads=1 \
       --seed=47