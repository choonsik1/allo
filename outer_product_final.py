"""

Explicit instantiation of one MAC unit per output element

"""
import allo
from allo.ir.types import int32
import allo.dataflow as df
import numpy as np
from allo.backend import hls
import tempfile


M=4
N=4
K=4



@df.kernel(mapping=[M, N], args=["A", "B"])
def matmul_outer(A: int32[M, K], B: int32[K, N]) -> int32[M, N]:
    """
    Explicitly instantiate 16 independent MAC units
    """
    
    C: int32[M,N] = 0
    
    # Outer product loop - fully unrolled in hardware
    for k in allo.grid(K):
    
        # parallel multiply-add operations
        # loop through inner dimension k
        
        for l in range(M):
        
          a_val = A[l,k]
          
          for m in range(N):
          
            C[l,m] += a_val * B[k,m]
            
    
    return C


# Schedule
s = allo.customize(matmul_outer)

# Partition everything to registers
s.partition(s.A)
s.partition(s.B)
s.partition(s.C)

# Pipeline the K loop
s.pipeline("k")

print(s.module)





# --- Simulation (functional verification) -------------------------------
def verify(schedule, label=""):
    """Allo-Kernel, NumPy comparison."""
    np.random.seed(42)
    A_np = np.random.randint(0, 10, size=(M, K)).astype(np.int32)
    B_np = np.random.randint(0, 10, size=(K, N)).astype(np.int32)
    C_ref = A_np @ B_np

    print(f"\n{label}")
    print(f"A:\n{A_np}")
    print(f"B:\n{B_np}")
    print(f"C Referenz (A @ B):\n{C_ref}")

    f = schedule.build(target="llvm")
    C_allo = f(A_np, B_np)

    print(f"C Allo:\n{C_allo}")

    max_err = np.max(np.abs(C_allo - C_ref))
    status = "PASSED" if max_err < 1e-5 else "FAILED"
    print(f"Maximal deviation: {max_err:.6e} ? {status}")
    return C_allo, C_ref




# --- ---------------------------------------
def generate_hls(schedule):
    """Vitis HLS C++ Code."""
    if not hls.is_available("vitis_hls"):
        print("Vitis HLS not available.")
        return

    print(f"\nGenerate HLS-Project:")
    try:
        with tempfile.TemporaryDirectory() as tmpdir:
            mod = schedule.build(
                target="vitis_hls",
                mode="hw_emu",
                project="outer_product_final",

            )
            print(f"HLS generation successful! Project in:")
            
    except Exception as e:
        print(f"HLS generation failed: {e}")
    return



if __name__ == "__main__":
    print("="*60)
    print("="*60)
    
    # Verification
    verify(s, label="Outer Product Kernel")
    
    # HLS generation
    generate_hls(s)