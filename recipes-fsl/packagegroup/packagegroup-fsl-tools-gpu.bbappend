# Replace new apitrace with old one from imx-gpu-viv

SOC_TOOLS_GPU_remove_imxgpu3d = " \
    imx-gpu-apitrace \
    imx-gpu-apitrace-bin \
"

SOC_TOOLS_GPU_append_imxgpu3d = " \
    imx-gpu-viv-tools-apitrace \
"
