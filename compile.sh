#!/usr/bin/bash

CXX_LINK_OPTIONS="-labsl_raw_hash_set -labsl_hashtablez_sampler -labsl_city -labsl_hash \
		-labsl_malloc_internal -labsl_throw_delegate -labsl_synchronization \
		-labsl_base -labsl_time -labsl_time_zone -labsl_stacktrace -labsl_log_severity -labsl_raw_logging_internal \
		-labsl_debugging_internal -labsl_spinlock_wait -labsl_malloc_internal -labsl_city \
        -lrte_eal -lrte_hash -lrte_mempool -lrte_ring -lrte_kvargs -lnuma \
        -l:librte_common_cpt.a -l:librte_common_dpaax.a -l:librte_common_ionic.a \
        -l:librte_common_octeontx.a -l:librte_bus_auxiliary.a -l:librte_bus_cdx.a \
        -l:librte_bus_fslmc.a -l:librte_bus_pci.a -l:librte_bus_platform.a -l:librte_bus_uacce.a \
        -l:librte_bus_vdev.a -l:librte_bus_vmbus.a -l:librte_common_mlx5.a -l:librte_common_nfp.a \
        -l:librte_common_nitrox.a -l:librte_common_qat.a -l:librte_common_sfc_efx.a \
        -l:librte_common_zsda.a -l:librte_mempool_bucket.a -l:librte_mempool_dpaa2.a \
        -l:librte_mempool_octeontx.a -l:librte_mempool_ring.a -l:librte_mempool_stack.a \
        -l:librte_dma_dpaa2.a -l:librte_dma_hisi_acc.a -l:librte_dma_hisi_pciep.a \
        -l:librte_dma_idxd.a -l:librte_dma_ioat.a -l:librte_dma_odm.a -l:librte_dma_skeleton.a \
        -l:librte_net_ark.a -l:librte_net_atlantic.a -l:librte_net_avp.a -l:librte_net_axgbe.a \
        -l:librte_net_bnxt.a -l:librte_net_cxgbe.a -l:librte_net_dpaa2.a -l:librte_net_ena.a \
        -l:librte_net_enetc.a -l:librte_net_enetfec.a -l:librte_net_enic.a -l:librte_net_gve.a \
        -l:librte_net_hinic.a -l:librte_net_hinic3.a -l:librte_net_hns3.a -l:librte_net_e1000.a \
        -l:librte_net_fm10k.a -l:librte_net_i40e.a -l:librte_net_iavf.a \
        -l:librte_net_ice.a -l:librte_net_idpf.a -l:librte_net_ixgbe.a -l:librte_net_cpfl.a \
        -l:librte_net_ionic.a -l:librte_net_memif.a -l:librte_net_mlx4.a -l:librte_net_mlx5.a \
        -l:librte_net_nbl.a -l:librte_net_netvsc.a -l:librte_net_nfp.a -l:librte_net_ngbe.a \
        -l:librte_net_ntnic.a -l:librte_net_null.a -l:librte_net_octeontx.a \
        -l:librte_net_octeon_ep.a -l:librte_net_qede.a -l:librte_net_r8169.a \
        -l:librte_net_ring.a -l:librte_net_rnp.a -l:librte_net_txgbe.a \
        -l:librte_net_vdev_netvsc.a -l:librte_net_vhost.a -l:librte_net_virtio.a \
        -l:librte_net_vmxnet3.a -l:librte_net_xsc.a -l:librte_net_zxdh.a -l:librte_crypto_bcmfs.a -l:librte_crypto_dpaa2_sec.a -l:librte_crypto_ionic.a -l:librte_crypto_mlx5.a -l:librte_crypto_nitrox.a -l:librte_crypto_null.a -l:librte_crypto_octeontx.a -l:librte_crypto_scheduler.a -l:librte_crypto_virtio.a -l:librte_compress_mlx5.a -l:librte_compress_nitrox.a -l:librte_regex_mlx5.a -l:librte_vdpa_ifc.a -l:librte_vdpa_mlx5.a -l:librte_vdpa_nfp.a -l:librte_vdpa_sfc.a -l:librte_pdcp.a -l:librte_ipsec.a -l:librte_vhost.a -l:librte_stack.a -l:librte_security.a -l:librte_sched.a -l:librte_reorder.a -l:librte_mldev.a -l:librte_regexdev.a -l:librte_pcapng.a -l:librte_ip_frag.a -l:librte_gpudev.a -l:librte_dispatcher.a -l:librte_eventdev.a -l:librte_dmadev.a -l:librte_cryptodev.a -l:librte_compressdev.a -l:librte_timer.a -l:librte_hash.a -l:librte_metrics.a -l:librte_cmdline.a -l:librte_pci.a -l:librte_ethdev.a -l:librte_meter.a -l:librte_net.a -l:librte_mbuf.a -l:librte_mempool.a -l:librte_rcu.a -l:librte_ring.a -l:librte_eal.a -l:librte_pmu.a -l:librte_telemetry.a -l:librte_argparse.a -l:librte_kvargs.a -l:librte_log.a -Wl,--no-whole-archive -Wl,--export-dynamic -L/home/mohammad/nemati/vpp/build/external/deb/debian/tmp/opt/vpp/external/x86_64/lib -l:libbnxt_re-rdmav59.a -l:libcxgb4-rdmav59.a -l:libefa.a -l:liberdma-rdmav59.a -l:libhns.a -l:libirdma-rdmav59.a -l:libmana.a -l:libmlx4.a -l:libmlx5.a -l:libmthca-rdmav59.a -l:libocrdma-rdmav59.a -l:libqedr-rdmav59.a -l:libvmw_pvrdma-rdmav59.a -l:libhfi1verbs-rdmav59.a -l:libipathverbs-rdmav59.a -l:librxe-rdmav59.a -l:libsiw-rdmav59.a -l:libibverbs.a"

mkdir -p bin

for target in $(ls benches/*$1*)
do
    full_filename="${target##*/}"
    extension="${full_filename##*.}"
    pure_filename="${full_filename%%\.$extension}"

    if [ "$extension" == "cpp" ]
    then
        clang++ benches/${pure_filename}.cpp -std=c++26 -O3 \
            -I/home/mohammad/nemati/rust-vs-cpp-datastructures/unordered_dense/include \
            -I/opt/vpp/external/x86_64/include -L/opt/vpp/external/x86_64/lib \
            $CXX_LINK_OPTIONS -o bin/cpp-${pure_filename}
    elif [ "$extension" == "rs" ]
    then
        rustc benches/${pure_filename}.rs -O -o bin/rust-${pure_filename}
    fi
done
