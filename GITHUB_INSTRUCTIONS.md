# How to Push Your LCC Node Project to GitHub

## Step-by-Step Guide

### Prerequisites

1. **Install Git**
   - Windows: Download from https://git-scm.com/
   - Mac: `brew install git` or use Xcode Command Line Tools
   - Linux: `sudo apt-get install git` (Ubuntu/Debian)

2. **Create GitHub Account**
   - Go to https://github.com
   - Sign up for free account
   - Verify your email

---

## Method 1: Using GitHub Desktop (Easiest!)

### Step 1: Install GitHub Desktop
- Download from: https://desktop.github.com/
- Install and launch

### Step 2: Sign In
- Click "Sign in to GitHub.com"
- Enter your credentials

### Step 3: Create Repository
1. Click "File → New Repository"
2. Name: `STM32-LCC-Node`
3. Description: `LCC/OpenLCB Node for STM32F303RE with MCP2515`
4. Local Path: Choose where to create it
5. Initialize with README: ✓ (checked)
6. Git Ignore: None (we have our own)
7. License: MIT
8. Click "Create Repository"

### Step 4: Copy Your Files
1. Open the repository folder (File → Show in Explorer/Finder)
2. Copy all your project files into this folder:
   ```
   arduino/
   docs/
   stm32cube/
   README.md
   LICENSE
   .gitignore
   ```

### Step 5: Commit Changes
1. GitHub Desktop will show all new files
2. Summary: "Initial commit - LCC Node implementation"
3. Description (optional): Add details
4. Click "Commit to main"

### Step 6: Publish to GitHub
1. Click "Publish repository"
2. Choose: Public or Private
3. Click "Publish Repository"

**Done!** 🎉 Your project is now on GitHub!

---

## Method 2: Using Command Line (Git)

### Step 1: Create Repository on GitHub

1. Go to https://github.com
2. Click the **"+"** icon (top right) → "New repository"
3. Repository name: `STM32-LCC-Node`
4. Description: `LCC/OpenLCB Node for STM32F303RE with MCP2515`
5. Public or Private: Choose
6. **DON'T** initialize with README (we have our own)
7. Click "Create repository"

### Step 2: Organize Your Local Files

Create this folder structure on your computer:

```
STM32-LCC-Node/
├── arduino/
│   ├── LCC_Node_Arduino/
│   │   └── LCC_Node_Arduino.ino
│   └── MCP2515_Test_Arduino/
│       └── MCP2515_Test_Arduino.ino
│
├── docs/
│   ├── ARDUINO_SETUP_GUIDE.md
│   ├── ARDUINO_QUICK_REFERENCE.md
│   ├── MCP2515_WIRING.md
│   ├── RJ45_CONNECTION_GUIDE.md
│   ├── RJ45_QUICK_START.md
│   ├── DUAL_RJ45_PASSTHROUGH.md
│   ├── BUS_POWERED_NODE.md
│   ├── BUS_POWER_SIMPLE.md
│   ├── LCC_PROTOCOL_REFERENCE.md
│   └── HARDWARE_WIRING.md
│
├── stm32cube/
│   ├── mcp2515.c
│   ├── mcp2515.h
│   ├── lcc_node_mcp2515.c
│   ├── lcc_node.h
│   └── main_mcp2515.c
│
├── README.md
├── LICENSE
└── .gitignore
```

### Step 3: Initialize Git Repository

Open terminal/command prompt in your project folder:

```bash
# Navigate to your project folder
cd path/to/STM32-LCC-Node

# Initialize git repository
git init

# Add all files
git add .

# Make first commit
git commit -m "Initial commit - LCC Node implementation with MCP2515"
```

### Step 4: Connect to GitHub

Replace `yourusername` with your actual GitHub username:

```bash
# Add remote repository
git remote add origin https://github.com/yourusername/STM32-LCC-Node.git

# Rename branch to main (if needed)
git branch -M main

# Push to GitHub
git push -u origin main
```

### Step 5: Enter Credentials

- Username: Your GitHub username
- Password: Your GitHub personal access token (NOT your password!)
  - Create token at: https://github.com/settings/tokens
  - Select: `repo` scope
  - Copy token and use as password

**Done!** 🎉

---

## Method 3: Using VS Code

### Step 1: Install VS Code
- Download from: https://code.visualstudio.com/

### Step 2: Open Project Folder
- File → Open Folder
- Select your project folder

### Step 3: Initialize Repository
1. Click Source Control icon (left sidebar)
2. Click "Initialize Repository"
3. Enter commit message: "Initial commit"
4. Click ✓ to commit

### Step 4: Publish to GitHub
1. Click "..." menu in Source Control
2. Select "Remote → Add Remote..."
3. Choose "Publish to GitHub"
4. Sign in to GitHub
5. Choose Public/Private
6. Click "Publish"

**Done!** 🎉

---

## Verify It Worked

Go to: `https://github.com/yourusername/STM32-LCC-Node`

You should see:
- ✅ Your README.md displayed
- ✅ All folders (arduino/, docs/, stm32cube/)
- ✅ LICENSE file
- ✅ .gitignore file

---

## Making Updates Later

### Using GitHub Desktop:
1. Make changes to files
2. GitHub Desktop shows changes
3. Write commit message
4. Click "Commit to main"
5. Click "Push origin"

### Using Command Line:
```bash
# After making changes
git add .
git commit -m "Description of changes"
git push
```

### Using VS Code:
1. Make changes
2. Source Control → Stage changes
3. Write commit message
4. Click ✓ to commit
5. Click "..." → Push

---

## Organizing Files for GitHub

Here's how to organize the files we created:

### Arduino Sketches
```
arduino/
├── LCC_Node_Arduino/
│   └── LCC_Node_Arduino.ino
└── MCP2515_Test_Arduino/
    └── MCP2515_Test_Arduino.ino
```

### Documentation
```
docs/
├── ARDUINO_SETUP_GUIDE.md
├── ARDUINO_QUICK_REFERENCE.md
├── MCP2515_WIRING.md
├── RJ45_CONNECTION_GUIDE.md
├── DUAL_RJ45_PASSTHROUGH.md
├── BUS_POWERED_NODE.md
└── LCC_PROTOCOL_REFERENCE.md
```

### STM32Cube Files
```
stm32cube/
├── mcp2515.c
├── mcp2515.h
├── lcc_node_mcp2515.c
└── main_mcp2515.c
```

---

## Best Practices

### Commit Messages
**Good:**
- ✅ "Add dual RJ45 pass-through support"
- ✅ "Fix MCP2515 initialization timing"
- ✅ "Update wiring diagram for bus power"

**Bad:**
- ❌ "Update"
- ❌ "Fixed stuff"
- ❌ "Changes"

### What to Commit
**Include:**
- ✅ Source code (.ino, .c, .h)
- ✅ Documentation (.md files)
- ✅ README.md
- ✅ LICENSE
- ✅ .gitignore

**Don't Include:**
- ❌ Build files (.hex, .elf, .bin)
- ❌ IDE settings (.vscode/, .settings/)
- ❌ Personal notes
- ❌ Binary files (unless necessary)

---

## Common Issues

### "Permission denied"
**Solution:** Set up SSH key or use personal access token
- Guide: https://docs.github.com/en/authentication

### "Repository not found"
**Solution:** Check repository name spelling and that it exists

### "Everything up-to-date"
**Solution:** You haven't made any changes since last push

### "Failed to push"
**Solution:** Pull latest changes first:
```bash
git pull origin main
# Resolve any conflicts
git push origin main
```

---

## Next Steps After Pushing

1. **Add Topics/Tags**
   - Go to repo on GitHub
   - Click ⚙️ near "About"
   - Add topics: `lcc`, `openlcb`, `stm32`, `mcp2515`, `model-railroad`

2. **Enable Discussions**
   - Settings → Features → Discussions

3. **Add Description**
   - Click ⚙️ near "About"
   - Add short description
   - Add website (if you have one)

4. **Create Releases**
   - When you have stable version
   - Releases → Create new release
   - Tag: v1.0.0
   - Title: "First Release"

5. **Share Your Project**
   - Post on LCC forums
   - Share on Reddit (r/modeltrains)
   - Add to Awesome lists

---

## Quick Reference Commands

```bash
# Check status
git status

# Add all files
git add .

# Commit with message
git commit -m "Your message"

# Push to GitHub
git push

# Pull latest changes
git pull

# View commit history
git log

# Create new branch
git checkout -b feature-name

# Switch branches
git checkout main

# See remotes
git remote -v
```

---

## GitHub Repository Features to Enable

### 1. Issues
- For bug reports and feature requests
- Already enabled by default

### 2. Discussions
- For questions and community
- Settings → Features → Enable Discussions

### 3. Wiki
- For detailed documentation
- Settings → Features → Enable Wiki

### 4. Projects
- For tracking development
- Projects tab → New project

### 5. GitHub Pages (optional)
- Host documentation website
- Settings → Pages → Enable

---

## Sample Repository Description

When creating repository, use this:

**Name:** `STM32-LCC-Node`

**Description:**
```
Complete LCC/OpenLCB node implementation for STM32F303RE with MCP2515 CAN controller. Includes Arduino sketches, hardware guides, and support for RJ45 connections and bus power.
```

**Topics:**
```
lcc
openlcb
stm32
stm32f303re
mcp2515
can-bus
model-railroad
arduino
embedded
electronics
```

---

## Congratulations! 🎉

Your project is now on GitHub and others can:
- ✅ View your code
- ✅ Download and use it
- ✅ Report issues
- ✅ Contribute improvements
- ✅ Fork for their own projects

**Share your repository link and help the LCC community!**

---

Need help? Issues with pushing? Let me know! 🚀
