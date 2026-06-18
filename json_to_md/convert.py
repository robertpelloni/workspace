import json
import sys
import os

def json_to_md(json_file_path, md_file_path):
    try:
        with open(json_file_path, 'r', encoding='utf-8') as f:
            data = json.load(f)

        title = data.get('title', 'Conversation')

        # OpenRouter PlayGround export structure:
        # - data['messages'] = dict of message metadata (id, type, characterId, items[])
        # - data['items'] = dict of actual content items (messageId, data.role, data.content[])
        messages_meta = data.get('messages', {})
        items_data = data.get('items', {})

        # Build a mapping: messageId -> list of items
        items_by_msg = {}
        for item_id, item in items_data.items():
            msg_id = item.get('messageId', '')
            if msg_id not in items_by_msg:
                items_by_msg[msg_id] = []
            items_by_msg[msg_id].append(item)

        # Sort messages by createdAt
        sorted_msgs = sorted(messages_meta.values(), key=lambda m: m.get('createdAt', ''))

        with open(md_file_path, 'w', encoding='utf-8') as f:
            f.write(f"# {title}\n\n")

            for msg in sorted_msgs:
                msg_id = msg.get('id', '')
                msg_type = msg.get('type', 'unknown')  # 'user' or 'assistant'
                character_id = msg.get('characterId', '')
                created_at = msg.get('createdAt', '')

                # Get items for this message
                msg_items = items_by_msg.get(msg_id, [])

                # Extract role and content from items
                for item in msg_items:
                    item_data = item.get('data', {})
                    role = item_data.get('role', msg_type)
                    content_parts = item_data.get('content', [])

                    # Build content text
                    text_parts = []
                    for part in content_parts:
                        if isinstance(part, dict):
                            part_type = part.get('type', '')
                            if part_type in ('input_text', 'output_text', 'text'):
                                text_parts.append(part.get('text', ''))
                            elif part_type == 'input_image':
                                img_url = part.get('image_url', {})
                                if isinstance(img_url, dict):
                                    text_parts.append(f"[Image: {img_url.get('url', 'embedded image')}]")
                                else:
                                    text_parts.append(f"[Image: {img_url}]")
                            elif part_type == 'tool_use':
                                text_parts.append(f"[Tool Use: {part.get('name', 'unknown')}]")
                                text_parts.append(f"```json\n{json.dumps(part.get('input', {}), indent=2)}\n```")
                            elif part_type == 'tool_result':
                                text_parts.append(f"[Tool Result]")
                                content_val = part.get('content', '')
                                if isinstance(content_val, list):
                                    for sub in content_val:
                                        if isinstance(sub, dict) and sub.get('type') == 'text':
                                            text_parts.append(sub.get('text', ''))
                                elif isinstance(content_val, str):
                                    text_parts.append(content_val)
                            else:
                                text_parts.append(json.dumps(part, indent=2))
                        elif isinstance(part, str):
                            text_parts.append(part)

                    full_text = '\n'.join(text_parts)

                    # Write to markdown
                    role_label = role.capitalize()
                    if character_id and character_id != 'USER':
                        role_label = f"{role_label} ({character_id})"

                    f.write(f"## {role_label}\n\n")
                    if created_at:
                        f.write(f"*{created_at}*\n\n")
                    f.write(f"{full_text}\n\n")
                    f.write("---\n\n")

        print(f"Successfully converted {json_file_path} to {md_file_path}")

    except Exception as e:
        print(f"An error occurred: {e}")
        import traceback
        traceback.print_exc()

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python convert.py <input.json> <output.md>")
    else:
        json_to_md(sys.argv[1], sys.argv[2])
