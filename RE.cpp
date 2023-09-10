DWORD dwScmOpcodeDebug=0;
BOOL bScmLocalDebug=FALSE;
BOOL bExceptionDisplayed=FALSE;

extern CChatWindow *pChatWindow;

int __declspec(naked) ExecuteScriptBuf()
{
    __asm
    {
        mov bScmLocalDebug, 1;

        mov eax, OFFSET ScriptBuf    // Move our script buffer base into eax.

        mov ecx, gst                // Move GAME_SCRIPT_THREAD structure into ecx.
        mov [ecx+0x14], eax            // Move eax into the gst->dwScriptIP.

        call ProcessOneCommand        // Call the game's script opcode processor.

        mov ecx, gst                // Move game script thread into ecx again.
        mov eax, [ecx+0xC5]            // Move the dwIfFlag into eax (return value).

        mov bScmLocalDebug, 0;

        ret                            // return.
    }
}
