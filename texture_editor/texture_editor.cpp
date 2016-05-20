#include "texture_editor/texture_editor.h"

void TextureEditor::RefreshDiaplay()
{
	m_textureDisplayer.SetTexture( m_cur_pTexture );
}