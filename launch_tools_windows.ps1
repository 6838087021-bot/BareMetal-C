# 1a. Navigate to the specific directory
# $env:USERNAME dynamically fetches the current user's name
$targetPath = "C:\Users\$env:USERNAME\Documents\BareMetal-C-Labs"

# Check if directory exists before trying to enter it
if (Test-Path -Path $targetPath) {
    Set-Location -Path $targetPath
    Write-Host "Changed directory to: $targetPath"
} else {
    Write-Error "Directory not found: $targetPath"
    exit 1
}

# 2. Launch Docker
# We use "${PWD}" to ensure the current path is passed correctly to Docker
docker run --name baremetal-c --rm -it -v "${PWD}:/labs" kongkrit/baremetal-c
